/*
 * DPT-Robot javascript library version 0.1
 * (c) 2014 DPTechnics
 * Author: Daan Pape
 *
 * Requires: JQuery, dpt-board
 */

function dptr_moveForward()
{
	dpt_setIO(21, true);
	dpt_setIO(22, true);
	dpt_setIO(24, false);
	dpt_setIO(18, false);
}

function dptr_moveBackward()
{
	dpt_setIO(24, true);
	dpt_setIO(18, true);
	dpt_setIO(21, false);
	dpt_setIO(22, false);
}

function dptr_moveLeft()
{
	dpt_setIO(21, true);
	dpt_setIO(24, false);
	dpt_setIO(22, false);
	dpt_setIO(18, false);
}

function dptr_moveRight()
{
	dpt_setIO(22, true);
	dpt_setIO(24, false);
	dpt_setIO(21, false);
	dpt_setIO(18, false);
}

function dptr_spinLeft() 
{
        dpt_setIO(22, true);
        dpt_setIO(24, true);
        dpt_setIO(18, false);
        dpt_setIO(21, false);
}

function dptr_spinRight()
{
        dpt_setIO(18, true);
        dpt_setIO(21, true);
        dpt_setIO(22, false);
        dpt_setIO(24, false);
}

function dptr_stopMotor()
{
	dpt_setIO(18, false);
	dpt_setIO(21, false);
	dpt_setIO(22, false);
	dpt_setIO(24, false);
}

function dptr_lightOn()
{
        dpt_setIO(6, true);
}

function dptr_lightOff()
{
        dpt_setIO(6, false);
}

/*
 * Listen to document keydown events to provide action attaching. 
 */
$(document).keydown(function(e){
});

/*
 * Listen to document keyup events to provide action attaching. 
 */
$(document).keyup(function(e){
});
