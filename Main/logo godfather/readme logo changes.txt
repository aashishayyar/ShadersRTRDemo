Changed the godfatherlogoAPI code 

to  adjust the speed of letter for animation
letter t is small it always animates fast so keep its value less then other letter and change values at respective positions

void logoAnimation(void)
{
	translate_r_y = translate_r_y + change_r;
	if (translate_r_y < -0.5f)
	{
		change_r = 1.0f; ---------------------change the value here to adjust speed of letter r
	}
	else if (translate_r_y > 0.2f)
	{
		change_r = -1.0f; ---------------------change the value here to adjust speed of letter r
	}


	translate_e_y = translate_e_y + change_e;
	if (translate_e_y < -4.7f)
	{
		change_e = 1.0f; ---------------------change the value here to adjust speed of letter e
	}
	else if (translate_e_y > -3.8f)
	{
		change_e = -1.0f; ---------------------change the value here to adjust speed of letter e
	}


	translate_h_y = translate_h_y + change_h;
	if (translate_h_y < -0.6f)
	{
		change_h = 1.0f; ---------------------change the value here to adjust speed of letter h
	}
	else if (translate_h_y > 0.5f)
	{
		change_h = -1.0f; ---------------------change the value here to adjust speed of letter h
	}


	translate_t_y = translate_t_y + change_t;
	if (translate_t_y < -0.2f)
	{
		change_t = 0.001f; -----change the value here to adjust speed of letter t keep low than others
	}
	else if (translate_t_y > 0.5f)
	{
		change_t = -0.001f; -----change the value here to adjust speed of letter t keep low than others
	}

	translate_f_y = translate_f_y + change_f;
	if (translate_f_y < -0.6f)
	
		change_f = 1.0f;-----change the value here to adjust speed of letter f
	}
	else if (translate_f_y > 0.3f)
	{
		change_f = -1.0f; -----change the value here to adjust speed of letter f
	}

}




i have uploading logo.h and main.h

just change the call in main.cpp  there is no there change if any please let me know
Thank you!!!!!!!!!