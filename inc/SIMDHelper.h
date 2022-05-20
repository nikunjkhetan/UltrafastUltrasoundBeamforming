#ifndef SIMDHELPER_H_INCLUDED
#define SIMDHELPER_H_INCLUDED

__m128d computePoint( const double* pIndex, const int16_t* pSignsColumn);

double computePointTwo( const double* pIndex, const int16_t* pSignsColumn );

//__m256d linearAVX( const double* pIndex, const int16_t* pRFCol, int N);

#endif // SIMDHELPER_H_INCLUDED
