# twosampleMR ####
## Load packages ####
if (!require(TwoSampleMR)) {
  BiocManager::install("TwoSampleMR")
}
library(TwoSampleMR)
## Work flow ####
### Read exposure GWAS ####
ect <-extract_instruments(outcomes='ukb-b-6235',clump=TRUE, r2=0.01,kb=5000,access_token = NULL)
### Read outcome GWAS ####
out <- extract_outcome_data(snps=ect$SNP,outcomes='finn-b-I9_MI',proxies = F,maf_threshold = 0.01,access_token = NULL)
mydata <- harmonise_data(exposure_dat=ect,outcome_dat=out,action= 2)
### MR analysis ####
res <- mr(mydata)
res <- generate_odds_ratios(res)
MRoutcome <- data.frame(res$method,res$nsnp,res$b,res$se,res$pval)
write.csv(MRoutcome,"MRoutcome.csv",row.names = F,quote = F)
### Heterogeneity test ####
het <- mr_heterogeneity(mydata)
if (T %in% (het$Q_pval < 0.05)) {
  res <- mr(mydata,method_list=c('mr_ivw_mre'))
}
### If the p_val < 0.05, the relation is significant
### pleiotropy test ####
pleio <- mr_pleiotropy_test(mydata)
write.csv(pleio,"pleio.csv",row.names = F,quote = F)
### Leave one out test ####
single <- mr_leaveoneout(mydata)
mr_leaveoneout_plot(single)
### Dot plot ####
mr_scatter_plot(res,mydata)
### Forest plot
res_single <- mr_singlesnp(mydata)
mr_forest_plot(res_single)
### Funnel plot ####
mr_funnel_plot(res_single)