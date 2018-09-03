//////////////////////////////////////////////////////////////////////////////
// * File name:    svf.c
// * 
// * Function:     svf                                                                        
// * Description:  Chamberlin state variable filter
// *               .
// *                                                                                     
// * Usage:        Int16  = svf(	 Int16 s,         // input sample
// *                                 Int16 findex, // sets the cutoff freq, range(0-254)
// *                                 Int16 Q1, //    sets the Q value, range(0-254)
// *                                 Int16 opmode,)//  switch between lowpass, highpass and bandpass.
// *
// * Erik Sandgren, Gustaf Johansson   2014-06-02                                                           
//////////////////////////////////////////////////////////////////////////////

#include "ezdsp5535.h"
#include "svf.h"

/* look up table with different cutoff freqs */
unsigned short F1[254] = {43,44,45,46,48,49,50,52,53,54,56,57,59,60,62,64,65,67,69,71,73,75,77,79,81,83,85,88,90,92,95,97,100,103,105,108,111,114,117,120,123,127,130,134,137,141,145,148,152,157,161,165,169,174,179,183,188,193,199,204,209,215,221,227,233,239,245,252,259,266,273,280,287,295,303,311,319,328,337,346,355,365,374,384,395,405,416,427,439,450,462,475,488,501,514,528,542,556,571,587,602,618,635,652,669,687,706,725,744,764,784,805,827,849,872,895,919,944,969,995,1022,1049,1077,1106,1135,1166,1197,1229,1262,1296,1330,1366,1403,1440,1479,1518,1559,1600,1643,1687,1732,1779,1826,1875,1925,1977,2030,2084,2140,2197,2256,2316,2378,2441,2506,2573,2642,2713,2785,2860,2936,3014,3095,3177,3262,3349,3439,3530,3624,3721,3820,3922,4027,4134,4244,4357,4473,4592,4714,4839,4968,5100,5235,5374,5516,5663,5813,5967,6124,6286,6452,6623,6798,6977,7161,7349,7542,7741,7944,8152,8365,8584,8808,9038,9274,9515,9762,10015,10274,10539,10811,11089,11373,11664,11962,12267,12578,12897,13222,13555,13895,14242,14596,14957,15326,15702,16086,16476,16874,17279,17691,18110,18536,18969,19408,19853,20304,20761,21223,21691,22162,22638,23117,23599,24082,24568,25053,25539,26023,26504,26982,27454,27920,28378};

Int16 svf(Int16 s, Int16 findex, Int16 Q1, Int16 opmode) {
				
				hVar1=(Int32)F1[findex] * D1;
            	hVar1= hVar1 >> 14;		
				outputs[0] = D2 +(Int16)hVar1;			//LP
				
				hVar2=(Int32)Q1*D1;
				hVar2=hVar2 >> 7;
    			outputs[1] = s - outputs[0] - (Int16)hVar2; //HP
   				
   				hVar3=(Int32)F1[findex]*outputs[1];
   				hVar3=hVar3>>14;
   				outputs[2] = (Int16)hVar3 + D1; // BP
   				
   				outputs[3] = outputs[1] + outputs[0]; // Notch
   				
   				D1 = outputs[2];
    			D2 = outputs[0];
    			
    			return outputs[opmode];
}