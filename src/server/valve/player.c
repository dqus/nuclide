/*
 * Copyright (c) 2016-2019 Marco Hladik <marco@icculus.org>
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

void weaponbox_spawn(player);

void player::Pain(int hit)
{
	
}

void player::Death(int hit)
{
	weaponbox_spawn(this);
	movetype = MOVETYPE_NONE;
	solid = SOLID_NOT;
	takedamage = DAMAGE_NO;
	flags &= ~FL_FLASHLIGHT;
	armor = activeweapon = g_items = 0;

	think = PutClientInServer;
	nextthink = time + 4.0f;
	sound(this, CHAN_AUTO, "fvox/flatline.wav", 1.0, ATTN_NORM);

	if (health < -50) {
		health = 0;
		Effect_GibHuman(origin);
		return;
	}

	health = 0;

	/* Let's handle corpses on the clientside */
	entity corpse = spawn();
	setorigin(corpse, origin + [0,0,32]);
	setmodel(corpse, model);
	setsize(corpse, VEC_HULL_MIN, VEC_HULL_MAX);
	corpse.movetype = MOVETYPE_TOSS;
	corpse.solid = SOLID_TRIGGER;
	corpse.modelindex = modelindex;
	corpse.frame = ANIM_DIESIMPLE;
	corpse.angles = angles;
	corpse.velocity = velocity;
}

/*
====================
UseWorkaround
====================
*/
void UseWorkaround(entity eTarget)
{
	eActivator = self;
	entity eOldSelf = self;
	self = eTarget;
	self.PlayerUse();
	self = eOldSelf;
}

/*
====================
Player_UseDown
====================
*/
void Player_UseDown(void)
{
	if (self.health <= 0) {
		return;
	} else if (!(self.gflags & GF_USE_RELEASED)) {
		return;
	}
	
	vector vSource;

	makevectors(self.v_angle);
	vSource = self.origin + self.view_ofs;
	traceline (vSource, vSource + (v_forward * 64), FALSE, self);

	if (trace_ent.PlayerUse) {
		self.gflags &= ~GF_USE_RELEASED;
		
		UseWorkaround(trace_ent);

		/* Some entities want to support Use spamming */
		if (!(self.gflags & GF_USE_RELEASED)) {
			sound(self, CHAN_ITEM, "common/wpn_select.wav", 0.25, ATTN_IDLE);
		}
	} else {
		sound(self, CHAN_ITEM, "common/wpn_denyselect.wav", 0.25, ATTN_IDLE);
		self.gflags &= ~GF_USE_RELEASED;
	}
}

/*
====================
Player_UseUp
====================
*/
void Player_UseUp(void) {
	if (!(self.gflags & GF_USE_RELEASED)) {
		self.gflags |= GF_USE_RELEASED;
	}
}

/*
=================
Player_SendEntity
=================
*/
float Player_SendEntity(entity ePEnt, float fChanged)
{
	player pl = (player)self;

	if (pl.health <= 0 && ePEnt != pl) {
		return FALSE;
	}

	WriteByte(MSG_ENTITY, ENT_PLAYER);
	WriteFloat(MSG_ENTITY, fChanged);

	/* really trying to get our moneys worth with 23 bits of mantissa */
	if (fChanged & PLAYER_MODELINDEX) {
		WriteShort(MSG_ENTITY, pl.modelindex);
	}
	if (fChanged & PLAYER_ORIGIN) {
		WriteCoord(MSG_ENTITY, pl.origin[0]);
		WriteCoord(MSG_ENTITY, pl.origin[1]);
	}
	if (fChanged & PLAYER_ORIGIN_Z) {
		WriteCoord(MSG_ENTITY, pl.origin[2]);
	}
	if (fChanged & PLAYER_ANGLES_X) {
		WriteFloat(MSG_ENTITY, pl.v_angle[0]);
	}
	if (fChanged & PLAYER_ANGLES_Y) {
		WriteFloat(MSG_ENTITY, pl.angles[1]);
	}
	if (fChanged & PLAYER_ANGLES_Z) {
		WriteFloat(MSG_ENTITY, pl.angles[2]);
	}
	if (fChanged & PLAYER_VELOCITY) {
		WriteCoord(MSG_ENTITY, pl.velocity[0]);
		WriteCoord(MSG_ENTITY, pl.velocity[1]);
	}
	if (fChanged & PLAYER_VELOCITY_Z) {
		WriteCoord(MSG_ENTITY, pl.velocity[2]);
	}
	if (fChanged & PLAYER_FLAGS) {
		WriteFloat(MSG_ENTITY, pl.flags);
	}
	if (fChanged & PLAYER_WEAPON) {
		WriteByte(MSG_ENTITY, pl.activeweapon);
	}
	if (fChanged & PLAYER_ITEMS) {
		WriteFloat(MSG_ENTITY, (__variant)pl.g_items);
	}
	if (fChanged & PLAYER_HEALTH) {
		WriteByte(MSG_ENTITY, pl.health);
	}
	if (fChanged & PLAYER_ARMOR) {
		WriteByte(MSG_ENTITY, pl.armor);
	}
	if (fChanged & PLAYER_MOVETYPE) {
		WriteByte(MSG_ENTITY, pl.movetype);
	}
	if (fChanged & PLAYER_VIEWOFS) {
		WriteFloat(MSG_ENTITY, pl.view_ofs[2]);
	}
	if (fChanged & PLAYER_BASEFRAME) {
		WriteByte(MSG_ENTITY, pl.baseframe);
	}
	if (fChanged & PLAYER_FRAME) {
		WriteByte(MSG_ENTITY, pl.frame);
	}
	if (fChanged & PLAYER_AMMO1) {
		WriteByte(MSG_ENTITY, pl.a_ammo1);
	}
	if (fChanged & PLAYER_AMMO2) {
		WriteByte(MSG_ENTITY, pl.a_ammo2);
	}
	if (fChanged & PLAYER_AMMO3) {
		WriteByte(MSG_ENTITY, pl.a_ammo3);
	}

	return TRUE;
}

void Weapons_Draw(void);
void CSEv_PlayerSwitchWeapon_f(float w)
{
	player pl = (player)self;
	pl.activeweapon = (int)w;
	Weapons_Draw();
}

void
Player_Precache(void)
{
	searchhandle pm;
	pm = search_begin("models/player/*/*.mdl", TRUE, TRUE);
	for (int i = 0; i < search_getsize(pm); i++) {
		precache_model(search_getfilename(pm, i));
	}
	search_end(pm);
}
