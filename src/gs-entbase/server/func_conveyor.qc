/*
 * Copyright (c) 2016-2022 Vera Visions LLC.
 *
 * Permission to use, copy, modify, and distribute this software for any
 * purpose with or without fee is hereby granted, provided that the above
 * copyright notice and this permission notice appear in all copies.
 *
 * THE SOFTWARE IS PROVIDED "AS IS" AND THE AUTHOR DISCLAIMS ALL WARRANTIES
 * WITH REGARD TO THIS SOFTWARE INCLUDING ALL IMPLIED WARRANTIES OF
 * MERCHANTABILITY AND FITNESS. IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR
 * ANY SPECIAL, DIRECT, INDIRECT, OR CONSEQUENTIAL DAMAGES OR ANY DAMAGES
 * WHATSOEVER RESULTING FROM LOSS OF MIND, USE, DATA OR PROFITS, WHETHER
 * IN AN ACTION OF CONTRACT, NEGLIGENCE OR OTHER TORTIOUS ACTION, ARISING
 * OUT OF OR IN CONNECTION WITH THE USE OR PERFORMANCE OF THIS SOFTWARE.
*/

/*QUAKED func_conveyor (0 .5 .8) ?
-------- KEYS --------
"targetname" : Name
"target" : Target when triggered.
"killtarget" : Target to kill when triggered.

STUB!

-------- TRIVIA --------
This entity was introduced in Half-Life (1998).
*/

#define SF_CONVEYOR_VISUAL	1
#define SF_CONVEYOR_NOTSOLID	2

class
func_conveyor:NSRenderableEntity
{
	float m_flSpeed;
	vector m_vecMoveDir;

	void(void) func_conveyor;

	virtual void(float) Save;
	virtual void(string,string) Restore;
	virtual void(void) Respawn;
	virtual void(entity, int) Trigger;
	virtual void(entity) Touch;
	virtual void(void) SetMovementDirection;
	virtual void(entity, string, string) Input;
	virtual void(string, string) SpawnKey;
};

void
func_conveyor::func_conveyor(void)
{
	m_flSpeed = 0.0f;
	m_vecMoveDir = [0.0f, 0.0f, 0.0f];
}

void
func_conveyor::Save(float handle)
{
	super::Save(handle);
	SaveFloat(handle, "m_flSpeed", m_flSpeed);
	SaveVector(handle, "m_vecMoveDir", m_vecMoveDir);
}

void
func_conveyor::Restore(string strKey, string strValue)
{
	switch (strKey) {
	case "m_flSpeed":
		m_flSpeed = ReadFloat(strValue);
		break;
	case "m_vecMoveDir":
		m_vecMoveDir = ReadVector(strValue);
		break;
	default:
		super::Restore(strKey, strValue);
	}
}

void
func_conveyor::SpawnKey(string strKey, string strValue)
{
	switch (strKey) {
	case "speed":
		m_flSpeed = stof(strValue);
		break;
	default:
		super::SpawnKey(strKey, strValue);
		break;
	}
}

void
func_conveyor::Respawn(void)
{
	if (!m_flSpeed)
		m_flSpeed = 100;

	RestoreAngles();
	SetMovementDirection();
	ClearAngles();
	SetModel(GetSpawnModel());
	SetMovetype(MOVETYPE_NONE);
	SetSolid(SOLID_BSP);

	Trigger(this, TRIG_ON);

	if (HasSpawnFlags(SF_CONVEYOR_NOTSOLID)) {
		SetSolid(SOLID_NOT);
		SetSkin(0);
	}
}

void
func_conveyor::SetMovementDirection(void)
{
	if (angles == [0,-1,0]) {
		m_vecMoveDir = [0,0,1];
	} else if (angles == [0,-2,0]) {
		m_vecMoveDir = [0,0,-1];
	} else {
		makevectors(angles);
		m_vecMoveDir = v_forward;
	}
}

void
func_conveyor::Touch(entity eToucher)
{
	if (HasSpawnFlags(SF_CONVEYOR_VISUAL))
		return;

	eToucher.basevelocity = m_vecMoveDir * (m_flSpeed * -0.2);
}

void 
func_conveyor::Trigger(entity act, int state)
{
	switch (state) {
	case TRIG_ON:
		m_flSpeed = fabs(m_flSpeed);
		break;
	case TRIG_OFF:
		m_flSpeed = -fabs(m_flSpeed);
		break;
	default:
		m_flSpeed = -m_flSpeed;
		break;
	}

	/* changes direction */
	glowmod[1] = 0.5f;
	glowmod[2] = m_flSpeed / 1024;
	SetSendFlags(RDENT_CHANGED_RENDERMODE);
}

void
func_conveyor::Input(entity eAct, string strInput, string strData)
{
	switch (strInput) {
	case "ToggleDirection":
		Trigger(eAct, TRIG_TOGGLE);
		break;
	case "SetSpeed":
		m_flSpeed = stof(strData);
		break;
	default:
		super::Input(eAct, strInput, strData);
	}
}
