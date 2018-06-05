
#include "fourier.hpp"
#include "vpa_n.h"

#include <cmath>
#include <fstream>
#include <map>

void calcFftIndices(int K, int* indices)
{
	int i, j ;
	int N ;

	N = (int)log2f(K) ;

	indices[0] = 0 ;
	indices[1 << 0] = 1 << (N - (0 + 1)) ;
	for (i = 1; i < N; ++i)
	{
		for(j = (1 << i) ; j < (1 << (i + 1)); ++j)
		{
			indices[j] = indices[j - (1 << i)] + (1 << (N - (i + 1))) ;
		}
	}
}

::vpa_n::VPAPrecision OP_16 = ::vpa_n::FLOAT;
::vpa_n::VPAPrecision OP_15 = ::vpa_n::FLOAT;
::vpa_n::VPAPrecision OP_14 = ::vpa_n::FLOAT;
::vpa_n::VPAPrecision OP_13 = ::vpa_n::FLOAT;
::vpa_n::VPAPrecision OP_12 = ::vpa_n::FLOAT;
::vpa_n::VPAPrecision OP_11 = ::vpa_n::FLOAT;
::vpa_n::VPAPrecision OP_10 = ::vpa_n::FLOAT;
::vpa_n::VPAPrecision OP_9 = ::vpa_n::FLOAT;
::vpa_n::VPAPrecision OP_8 = ::vpa_n::FLOAT;
::vpa_n::VPAPrecision OP_7 = ::vpa_n::FLOAT;
::vpa_n::VPAPrecision OP_6 = ::vpa_n::FLOAT;
::vpa_n::VPAPrecision OP_5 = ::vpa_n::FLOAT;
::vpa_n::VPAPrecision OP_4 = ::vpa_n::FLOAT;
::vpa_n::VPAPrecision OP_3 = ::vpa_n::FLOAT;
::vpa_n::VPAPrecision OP_2 = ::vpa_n::FLOAT;
::vpa_n::VPAPrecision OP_1 = ::vpa_n::FLOAT;
::vpa_n::VPAPrecision OP_0 = ::vpa_n::FLOAT;
void radix2DitCooleyTykeyFft(int K, int* indices, Complex* x, Complex* f)
{

	calcFftIndices(K, indices) ;

	int step ;
	float arg ;
	int eI ;
	int oI ;

	float fftSin;
	float fftCos;

	Complex t;
	int i ;
	int N ;
	int j ;
	int k ;
	float tmp1, tmp2;

	double dataIn[1];
	double dataOut[2];

	for(i = 0, N = 1 << (i + 1); N <= K ; i++, N = 1 << (i + 1))
	{
		for(j = 0 ; j < K ; j += N)
		{
			step = N >> 1 ;
			for(k = 0; k < step ; k++)
			{
// 				tmp1 = (float)k;
// 				tmp2 = (float)N;
// 				arg = tmp1 / tmp2 ;
 
				arg =(float)( ::vpa_n::VPA((float)k, OP_0)/::vpa_n::VPA((float)N, OP_0));

				eI = j + k ; 
				oI = j + step + k ;

				dataIn[0] = arg;

//#pragma parrot(input, "fft", [1]dataIn)

				fftSinCos(arg, &fftSin, &fftCos);

				dataOut[0] = fftSin;
				dataOut[1] = fftCos;

//#pragma parrot(output, "fft", [2]<0.0; 2.0>dataOut)

				fftSin = dataOut[0];
				fftCos = dataOut[1];


				// Non-approximate
				t =  x[indices[eI]] ;
				x[indices[eI]].real =(float)( ::vpa_n::VPA(t.real , OP_1) +::vpa_n::VPA( (::vpa_n::VPA(::vpa_n::VPA(x[indices[oI]].real , OP_3)* ::vpa_n::VPA(fftCos, OP_3) , OP_2)- ::vpa_n::VPA(::vpa_n::VPA(x[indices[oI]].imag , OP_4)* ::vpa_n::VPA(fftSin, OP_4), OP_2)), OP_1)/*II OP_1*/ );
                x[indices[eI]].imag =(float)( ::vpa_n::VPA(t.imag , OP_5) +::vpa_n::VPA( (::vpa_n::VPA(::vpa_n::VPA(x[indices[oI]].imag , OP_7)* ::vpa_n::VPA(fftCos, OP_7) , OP_6)+ ::vpa_n::VPA(::vpa_n::VPA(x[indices[oI]].real , OP_8)* ::vpa_n::VPA(fftSin, OP_8), OP_6)), OP_5)/*II OP_5*/ );

                x[indices[oI]].real =(float)( ::vpa_n::VPA(t.real , OP_9) -::vpa_n::VPA( (::vpa_n::VPA(::vpa_n::VPA(x[indices[oI]].real , OP_11)* ::vpa_n::VPA(fftCos, OP_11) , OP_10)- ::vpa_n::VPA(::vpa_n::VPA(x[indices[oI]].imag , OP_12)* ::vpa_n::VPA(fftSin, OP_12), OP_10)), OP_9)/*II OP_9*/ );
                x[indices[oI]].imag =(float)( ::vpa_n::VPA(t.imag , OP_13) -::vpa_n::VPA( (::vpa_n::VPA(::vpa_n::VPA(x[indices[oI]].imag , OP_15)* ::vpa_n::VPA(fftCos, OP_15) , OP_14)+ ::vpa_n::VPA(::vpa_n::VPA(x[indices[oI]].real , OP_16)* ::vpa_n::VPA(fftSin, OP_16), OP_14)), OP_13)/*II OP_13*/ );
			}
		}
	}

	for (int i = 0 ; i < K ; i++)
	{
		f[i] = x[indices[i]] ;
	}
}
