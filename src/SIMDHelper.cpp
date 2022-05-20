#include "incHeaders.h"
#include "incCustomHeader.h"

// pIndex: pointer to the current idxt value.
// pSignsColumn: pointer to the first element in the column of SIG
__m128d computePoint( const double* pIndex, const int16_t* pSignsColumn)
{
    // Load the index value into both lanes of the vector
    __m128d idx = _mm_loaddup_pd( pIndex );

    // Convert into int32 with truncation; this assumes the number there ain't negative.
    int iFloor = _mm_cvttsd_si32( idx );

    // Compute fractional part
    idx = _mm_sub_pd( idx, _mm_floor_pd( idx ) );
    // Compute interpolation coefficients, they are [ 1.0 - idx, idx ]
    // _mm_set_sd copies 1.0 to lower half and zero to upper half
    // _mm_addsub_pd(a,b) subtracts lower half of b from a and adds upper half of b to a
    idx = _mm_addsub_pd( _mm_set_sd( 1.0 ), idx );

    #define _mm_loadu_si32(p) _mm_cvtsi32_si128(*(const int*)(p))
    // Load two int16_t values from sequential addresses
    const __m128i signsInt = _mm_loadu_si32( pSignsColumn + iFloor );
    // Upcast them to int32, then to fp64
    const __m128d signs = _mm_cvtepi32_pd( _mm_cvtepi16_epi32( signsInt ) );

    // Load validation index into vector
//     __m128d vIdx = _mm_loaddup_pd( validIDX );

    // Compute the result
    const __m128d res = _mm_mul_pd( idx, signs );

    return res;
}

double computePointTwo( const double* pIndex, const int16_t* pSignsColumn )
{
    // Load the index value into both lanes of the vector
    __m128d idx = _mm_loaddup_pd( pIndex );

    // Convert into int32 with truncation; this assumes the number there ain't negative.
    const int iFloor = _mm_cvttsd_si32( idx );

    // Compute fractional part
    idx = _mm_sub_pd( idx, _mm_floor_pd( idx ) );
    // Compute interpolation coefficients, they are [ 1.0 - idx, idx ]
    idx = _mm_addsub_pd( _mm_set_sd( 1.0 ), idx );

    // Load two int16_t values from sequential addresses
    const __m128i signsInt = _mm_loadu_si32( pSignsColumn + iFloor );
    // Upcast them to int32, then to fp64
    const __m128d signs = _mm_cvtepi32_pd( _mm_cvtepi16_epi32( signsInt ) );

    // Compute the result
    __m128d res = _mm_mul_pd( idx, signs );
    res = _mm_add_sd( res, _mm_unpackhi_pd( res, res ) );
    // The above 2 lines (3 instructions) can be replaced with the following one:
    // const __m128d res = _mm_dp_pd( idx, signs, 0b110001 );
    // It may or may not be better, the dppd instruction is not particularly fast.

    return _mm_cvtsd_f64( res );
}

// Perform linear interpolation using AVX instructions.
//      pIndex  - pointer to value in idxt array
//      pRFCol  - pointer to first channel of RF data
//      N       - number of elements in a single RF channel
//__m256d linearAVX( const double* pIndex, const int16_t* pRFCol, int N)
//{
//    // Load 4 idxt values
//    __m256d idxt = _mm256_loadu_pd( pIndex );
//
//    // Compute idxf and idxd values
//     __m256d idxf = _mm256_floor_pd( idxt );
//     __m256d idxd = _mm256_sub_pd( idxt, idxf );
//
//     // Compute s1...sN
//     __m256d s1 = _mm256_sub_pd( _mm256_set1_pd( 1.0 ), idxd ); // Note, s2 = idxd for linear interp
//
//     // Gather RF values
//     int base_addr = static_cast<int>(*pIndex);
//     __m128i vindex = _mm_set_epi32(0,N-base_addr,2*N-base_addr,3*N-base_addr);        // NOTE: CHECK THAT THIS IS CORRECT WAY TO PASS VALUES
//     __m128i rfVals = _mm_i32gather_epi32( (const int*) (base_addr + pRFCol),vindex,2);
//
//     // Upconvert, shuffle and separate
//     __m256i rfUpconv = _mm256_cvtepi16_epi32(rfVals);
//     __m256i rfShuf = _mm256_permute4x64_epi64(_mm256_shuffle_epi32(rfUpconv,216),216); // 216 = 0b11011000 in binary, 0xD8 in Hex. See documentation
//     // Additional note: using _mm256_permutevar8x32_epi32 may be faster? Experiment with this and find out later
//
//     __m256d rf1 = _mm256_cvtepi32_pd(_mm256_extracti128_si256(rfShuf,0));
//     __m256d rf2 = _mm256_cvtepi32_pd(_mm256_extracti128_si256(rfShuf,1));
//
//     // Multiply coeffs and sum to get result
//     __m256d result = _mm256_add_pd(_mm256_mul_pd(rf1,s1),_mm256_mul_pd(rf2,idxd));
//
//     return result;
//
//}
