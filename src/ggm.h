#ifndef GGM_H
#define GGM_H 1

// Important: this definition ensures Armadillo enables SuperLU
// Commented out as the configuration of SuperLU is system-dependent
//#define ARMA_USE_SUPERLU 1

// we only include RcppArmadillo.h which pulls Rcpp.h in for us
#include "RcppArmadillo.h"

// via the depends attribute we tell Rcpp to create hooks for
// RcppArmadillo so that the build process will know what to do
//
// [[Rcpp::depends(RcppArmadillo)]]


#include "crossprodmat.h"
#include "cstat.h"

using namespace Rcpp;
using namespace std;



//*************************************************************************************
// CLASS ggmObject
//*************************************************************************************

class ggmObject {

public:

  //Constructor and destructor

  ggmObject(NumericMatrix y, List prCoef, List prModel, List samplerPars);
  ~ggmObject();

  //PUBLIC METHODS PROVIDED BY THE CLASS

  int n();    //sample size nrow(y)
  int ncol(); //number of variables ncol(y)

  CharacterVector sampler(); //sampler type
  int niter();
  int burnin();

private:

  NumericMatrix y;

  List prCoef;  //prior on parameters
  List prModel; //prior on model
  List samplerPars; //posterior sampler parameters

};




//*************************************************************************************
// FUNCTIONS
//*************************************************************************************


//void print_mat( mat_type A );
//void print_mat(arma::mat *A);
//void print_spmat(arma::sp_mat *A);

arma::sp_mat modelSelectionGGMC(NumericMatrix y, List prCoef, List prModel, List samplerPars, arma::sp_mat Omegaini);

void spmat_droprowcol(arma::sp_mat *A_minusj, arma::sp_mat *A, int *j);

void GGM_Gibbs(arma::sp_mat *ans, ggmObject *ggm, arma::sp_mat *Omegaini);

void GGM_Gibbs_singlecol(arma::sp_mat *ans, int iter, int colid, ggmObject *ggm, arma::sp_mat *Omegacol, arma::mat *invOmega_rest);



#endif /* MODELSEL_H */