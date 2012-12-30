
/*
 * Copyright (c) 2012, Robert Olsson, Herjulf Utveckling, Uppsala, Sweden
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 * 3. Neither the name of the Institute nor the names of its contributors
 *    may be used to endorse or promote products derived from this software
 *    without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COMPANY AND CONTRIBUTORS ``AS IS'' AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED.  IN NO EVENT SHALL THE INSTITUTE OR CONTRIBUTORS BE LIABLE
 * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS
 * OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
 * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
 * LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY
 * OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF
 * SUCH DAMAGE.
 *
 *
 * Author: Robert Olsson <robert@herjulf.se>

 Note! VH400 is sensitive for different type of soils according to leading
 agricultural expert Abraham Joel. SLU. Uppsala. Sweden. This transform is 
 with "200g of Miracle Grow Potting Soil" which is what the vendor provides 
 at their web-site.  Other soils probably needs other functions.
 The sensors we have is Rev F.

 References:

 http://www.vegetronix.com/Curves/VH400-RevA/VG400-RevA-Curves.phtml
 also
 http://vegetronix.com/Products/VH400/VH400-Piecewise-Curve.phtml


 Program, reads voltage on stdin, prints VWC value on stdout. 

 */

#include <stdio.h>

double VWC_VH400_RevA(double v)
{

  if(v < 0.1) 
    return 0;

 /* 1st Line (0, 0.1) (10, 1.1) --> VC = 10v - 1 for ( 0.1 < v <= 1.1) */
   if(v >= 0.1 && v <= 1.1) 
      return 10*v - 1;

 /* 2:nd Line (10, 1.1) (15, 1.3) --> VC = 25v - 17.5 for ( 1.1 < v <= 1.3) */
   if(v > 1.1 && v <= 1.3) 
      return 25*v - 17.5;

   if(v > 1.3 && v <= 1.82) 
      return 48.08*v - 47.5;

   if(v > 1.82 && v <= 2.2) 
      return 26.32*v - 7.89;

   return 26.32*v - 7.89; // Out of range. Follow last line.
}


int main()
{
  int i;
  double vin;

  if( scanf("%lf", &vin) > 0)  
    printf("%-5.1f\n", VWC_VH400_RevA(vin));
	   
#ifdef TEST 
	   for(i = 0; i < 240; i += 5) 
	     printf("%5.2f %5.1f\n",((double) i)/100., VWC_VH400_RevA( ((double) i)/100.));
#endif
  return 0;
}
