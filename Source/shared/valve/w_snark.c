/***
*
*	Copyright (c) 2016-2019 Marco 'eukara' Hladik. All rights reserved.
*
*	See the file LICENSE attached with the sources for usage details.
*
****/

enum
{
	SNARK_IDLE,
	SNARK_FIDGET1,
	SNARK_FIDGET2,
	SNARK_HOLSTER,
	SNARK_DRAW,
	SNARK_THROW
};

void w_snark_pickup(void)
{
#ifdef SSQC
	player pl = (player)self;
	pl.ammo_snark = bound(0, pl.ammo_snark + 1, 10);
#endif
}

void w_snark_draw(void)
{
#ifdef CSQC
	Weapons_ViewAnimation(SNARK_DRAW);
#else
	player pl = (player)self;
	Weapons_UpdateAmmo(pl, __NULL__, pl.ammo_snark, __NULL__);
#endif
}

void w_snark_holster(void)
{
	
}

#ifdef SSQC
void w_snark_deploy(void)
{
	static void snark_ai(void)
	{
		input_movevalues = [250,0,0];
		input_buttons = 0;
		input_impulse = 0;
		input_angles = self.angles;
		input_timelength = frametime;
	
		if (self.health <= 0) {
			return;
		}

		if (self.weapon <= 0.0 && self.aiment == __NULL__) {
			float shortest = 999999;
			for (entity ef = world; (ef = find(ef, classname, "player"));) {
				float len = vlen(ef.origin - self.origin);
				if (len < shortest && ef.health > 0) {
					self.owner = __NULL__;
					self.aiment = ef;
					shortest = len;
					setsize(self, [-16,-16,0],[16,16,32]);
				}
			}
		} 

		if (self.aiment) {
			self.angles = input_angles = vectoangles(self.aiment.origin - self.origin);
		}

		if (self.aiment && self.weapon <= 0.0) {
			self.weapon = 0.5f + random();
			sound(self, CHAN_VOICE, sprintf("squeek/sqk_hunt%d.wav",floor(random(1,4))), 1.0, ATTN_NORM);
			input_buttons = 2;
			Damage_Apply(self, world, 1, self.origin, TRUE);
			
			makevectors(self.angles);
			traceline(self.origin, self.origin + (v_forward * 128), 0, self);
			
			if (trace_ent.classname == "player") {
				float pit = 100 + random(0,10);
				sound(self, CHAN_BODY, "squeek/sqk_deploy1.wav", 1.0, ATTN_NORM, pit);
				Damage_Apply(trace_ent, self, 5, trace_endpos, FALSE);
			}

			if (self.aiment.health <= 0) {
				self.aiment = __NULL__;
			}
		}
		self.weapon -= frametime;	
		runstandardplayerphysics(self);
	}
	static void snark_die(int i) {
		sound(self, CHAN_VOICE, "squeek/sqk_die1.wav", 1.0, ATTN_NORM);
		sound(self, CHAN_BODY, "squeek/sqk_blast1.wav", 1.0, ATTN_NORM);
		self.customphysics = __NULL__;
		remove(self);
	}
	static void snark_pain(int i) { }
	entity snark = spawn();
	snark.owner = self;
	setmodel(snark, "models/w_squeak.mdl");
	makevectors(self.v_angle);
	setorigin(snark, self.origin + v_forward * 32);
	snark.solid = SOLID_BBOX;
	snark.movetype = MOVETYPE_WALK;
	snark.frame = 3; /* running like crazy. */
	snark.customphysics = snark_ai;
	snark.angles = self.angles;
	snark.health = 30;
	snark.vPain = snark_pain;
	snark.takedamage = DAMAGE_YES;
	snark.aiment = __NULL__;
	snark.vDeath = snark_die;
	snark.weapon = 3.0f;
}
#endif

void w_snark_primary(void)
{
	player pl = (player)self;	
	if (pl.w_attack_next > 0.0) {
		return;
	}

	/* Ammo check */
#ifdef CSQC
	if (pl.a_ammo2 <= 0) {
		return;
	}
#else
	if (pl.ammo_snark <= 0) {
		return;
	}
#endif


	/* Audio-Visual Bit */
#ifdef CSQC
	Weapons_ViewAnimation(SNARK_THROW);
	pl.a_ammo2--;
#else
	w_snark_deploy();
	pl.ammo_snark--;
	Weapons_UpdateAmmo(pl, __NULL__, pl.ammo_snark, __NULL__);
	
	if (pl.a_ammo2 <= 0) {
		Weapons_RemoveItem(pl, WEAPON_SNARK);
	}

#endif

	pl.w_idle_next = 1.0f;
	pl.w_attack_next = 0.25f;

}
void w_snark_secondary(void)
{
	
}
void w_snark_reload(void)
{
	
}
void w_snark_release(void)
{
	int r;
	player pl = (player)self;
	if (pl.w_idle_next > 0.0) {
		return;
	}

	r = floor(random(0,3));
	switch (r) {
	case 0:
		Weapons_ViewAnimation(SNARK_IDLE);
		pl.w_idle_next = 1.875f;
		break;
	case 1:
		Weapons_ViewAnimation(SNARK_FIDGET1);
		pl.w_idle_next = 4.375f;
		break;
	default:
		Weapons_ViewAnimation(SNARK_FIDGET2);
		pl.w_idle_next = 5.0f;
		break;
	}
}
void w_snark_precache(void)
{
	precache_model("models/w_squeak.mdl");
	precache_model("models/p_squeak.mdl");
	precache_model("models/v_squeak.mdl");	
	precache_sound("squeek/sqk_deploy1.wav");
	precache_sound("squeek/sqk_die1.wav");
	precache_sound("squeek/sqk_blast1.wav");
	precache_sound("squeek/sqk_hunt1.wav");
    precache_sound("squeek/sqk_hunt2.wav");
    precache_sound("squeek/sqk_hunt3.wav");
}
string w_snark_vmodel(void)
{
	return "models/v_squeak.mdl";
}
string w_snark_wmodel(void)
{
	return "models/w_sqknest.mdl";
}
string w_snark_pmodel(void)
{
	return "models/p_squeak.mdl";
}
string w_snark_deathmsg(void)
{
	return "";
}


float w_snark_aimanim(void)
{
	return self.flags & FL_CROUCHING ? ANIM_CR_AIMSQUEAK : ANIM_AIMSQUEAK;
}

void w_snark_hud(void)
{
#ifdef CSQC
	HUD_DrawAmmo2();
#endif
}

void w_snark_hudpic(int s, vector pos)
{
#ifdef CSQC
	if (s) {
		drawsubpic(pos, [170,45], "sprites/640hud6.spr_0.tga", [0,135/256], [170/256,45/256], g_hud_color, 1, DRAWFLAG_ADDITIVE);
	} else {
		drawsubpic(pos, [170,45], "sprites/640hud3.spr_0.tga", [0,135/256], [170/256,45/256], g_hud_color, 1, DRAWFLAG_ADDITIVE);
	}
#endif
}

weapon_t w_snark =
{
	ITEM_SNARK,
	4,
	3,
	w_snark_draw,
	w_snark_holster,
	w_snark_primary,
	w_snark_secondary,
	w_snark_reload,
	w_snark_release,
	w_snark_hud,
	w_snark_precache,
	w_snark_pickup,
	w_snark_vmodel,
	w_snark_wmodel,
	w_snark_pmodel,
	w_snark_deathmsg,
	w_snark_aimanim,
	w_snark_hudpic
};

#ifdef SSQC
void weapon_snark(void) {
	Weapons_InitItem(WEAPON_SNARK);
}
#endif
