/***
*
*	Copyright (c) 2016-2019 Marco 'eukara' Hladik. All rights reserved.
*
*	See the file LICENSE attached with the sources for usage details.
*
****/

.int iMag_FIVESEVEN;

// Weapon Info
weaponinfo_t wptFIVESEVEN = { 
	WEAPON_FIVESEVEN, 	// Identifier
	SLOT_SECONDARY,		// Slot
	750, 				// Price
	CALIBER_57MM, 		// Caliber ID
	1.0, 				// Max Player Speed
	1, 					// Bullets Per Shot
	20, 				// Clip/MagSize
	25, 				// Damage Per Bullet
	1, 					// Penetration Multiplier
	4096, 				// Bullet Range
	0.885, 				// Range Modifier
	TYPE_SEMI,			// Firing Type
	0.15, 				// Attack-Delay
	3.1, 				// Reload-Delay
	iAmmo_57MM, 		// Caliber Pointer
	iMag_FIVESEVEN, 	// Clip Pointer
	200,				// Accuracy Divisor
	0.55,				// Accuracy Offset
	1.4,				// Max Inaccuracy
	8,					// Minimum Crosshair Distance
	3,					// Crosshair Movement Delta
	1.5,				// Armor penetration ratio
	ATYPE_ONEHAND,		// Animation Type
	SHELL_PISTOL
};

// Anim Table
enum {
	ANIM_FIVESEVEN_IDLE,
	ANIM_FIVESEVEN_SHOOT1,
	ANIM_FIVESEVEN_SHOOT2,
	ANIM_FIVESEVEN_SHOOT_EMPTY,
	ANIM_FIVESEVEN_RELOAD,
	ANIM_FIVESEVEN_DRAW
};

void WeaponFIVESEVEN_Draw( void ) {
#ifdef SSQC
	BaseGun_Draw();
#else
	View_PlayAnimation( ANIM_FIVESEVEN_DRAW );
#endif
}

void WeaponFIVESEVEN_PrimaryFire( void ) {
#ifdef SSQC
	if ( BaseGun_PrimaryFire() == TRUE ) {
		// Play Sound
		sound( self, CHAN_WEAPON, "weapons/fiveseven-1.wav", 1, ATTN_NORM );
	}
#else
	if ( getstatf( STAT_CURRENT_MAG ) == 0 ) {
		View_PlayAnimation( ANIM_FIVESEVEN_SHOOT_EMPTY );
	} else {
		if ( random() <= 0.5 ) {
			View_PlayAnimation( ANIM_FIVESEVEN_SHOOT1 );
		} else {
			View_PlayAnimation( ANIM_FIVESEVEN_SHOOT2 );
		}
	}
	BaseGun_ShotMultiplierHandle( 1 );
#endif
}

void WeaponFIVESEVEN_Reload( void ) {
#ifdef SSQC
	if ( BaseGun_Reload() == TRUE ) {
	}
#else
	View_PlayAnimation( ANIM_FIVESEVEN_RELOAD );
#endif
}
