***** USAGE ****

GUN_DRAW();

Call 	GUN_DRAW(); in Render to Draw the Gun on Screen.

to Rescale the Gun Size , Call glScalef(); accordingly before GUN_DRAW();

eg : // glScalef(0.2, 0.2, 0.5); // to make gun smaller increase z cordinate accordingly.

to Stop rotating of GUN , set _gGunAngle = someAngle in GUN_UPDATE(); hard coded in last line of  GUN_UPDATE();


void GUN_UPDATE()
{
	if (_gGunAngle >= 360.0f)
		_gGunAngle = 0.0f;
	else
		_gGunAngle += 0.5f;

	_gGunAngle  = 10.0f // example
}

***************************************************************************************************


