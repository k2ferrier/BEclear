#include <Rcpp.h>
using namespace Rcpp;
//' Calculating the Local Loss
//' 
//' @keywords internal
//' 
//' @description Calculates the gradient dR and dL for the current epoch.
//' 
//' @return a list containing two matrices containing the local loss
//'
//' @import Rcpp
//' @export localLoss
// [[Rcpp::export]]
SEXP localLoss(const NumericMatrix& L,const NumericMatrix& R, 
               const NumericVector& is, const NumericVector& js, 
               const NumericMatrix& error_matrix) {
    
    NumericMatrix dL(L.nrow(), L.ncol());
    NumericMatrix dR(R.nrow(), R.ncol());
    for(int n = 0; n < is.size(); n++){
        int row = is[n] - 1;
        int column  = js[n] - 1;
        double x = error_matrix(row, column);
        
        dL(row, _) = dL(row, _) + x * R(_ , column);
        dR(_ , column) = dR(_ , column) + x * L(row, _);
        
        

    }
    return List::create(  _["dL"]  = dL, _["dR"]  = dR );
}


