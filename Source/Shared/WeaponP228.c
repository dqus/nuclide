/***
*
*	Copyright (c) 2016-2019 Marco 'eukara' Hladik. All rights reserved.
*
*	See the file LICENSE attached with the sources for usage details.
*
****/

.int iMag_P228;

// Weapon Info
weaponinfo_t wptP228 = { 
	WEAPON_P228, 		// Identifier
	SLOT_SECONDARY,		// Slot
	600, 				// Price
	CALIBER_357SIG, 	// Caliber ID
	1.0, 				// Max Player Speed
	1, 					// Bullets Per Shot
	13, 				// Clip/MagSize
	40, 				// Damage Per Bullet
	1, 					// Penetration Multiplier
	4096, 				// Bullet Range
	0.8, 				// Range Modifier
	TYPE_SEMI,			// Firing Type
	0.15, 				// Attack-Delay
	2.7, 				// Reload-Delay
	iAmmo_357SIG, 		// Caliber Pointer
	iMag_P228, 			// Clip Pointer
	200,				// Accuracy Divisor
	0.55,				// Accuracy Offset
	1.4,				// Max Inaccuracy
	8,					// Minimum Crosshair Distance
	3,					// Crosshair Movement Delta
	1.25,				// Armor penetration ratio
	ATYPE_ONEHAND,		// Animation Type
	SHELL_PISTOL
};

// Anim Table
enum {
	ANIM_P228_IDLE,
	ANIM_P228_SHOOT1,
	ANIM_P228_SHOOT2,
	ANIM_P228_SHOOT3,
	ANIM_P228_SHOOT_EMPTY,
	ANIM_P228_RELOAD,
	ANIM_P228_DRAW
};

void WeaponP228_Draw( void ) {
#ifdef SSQC
	BaseGun_Draw();
#else
	View_PlayAnimation( ANIM_P228_DRAW );
#endif
}

void WeaponP228_PrimaryFire( void ) {
#ifdef SSQC
	if ( BaseGun_PrimaryFire() == TRUE ) {
		// Play Sound
		sound( self, CHAN_WEAPON, "weapons/p228-1.wav", 1, ATTN_NORM );
	}
#else
	if ( getstatf( STAT_CURRENT_MAG ) == 0 ) {
		View_PlayAnimation( ANIM_P228_SHOOT_EMPTY );
	} else {
		
		int iRand = (int)floor( random( 1, 4 ) );
		
		if ( iRand == 1 ) {
			View_PlayAnimation( ANIM_P228_SHOOT1 );
		} else if ( iRand == 2 ) {
			View_PlayAnimation( ANIM_P228_SHOOT2 );
		} else {
			View_PlayAnimation( ANIM_P228_SHOOT3 );
		}
	}
	BaseGun_ShotMultiplierHandle( 1 );
#endif
}

void WeaponP228_Reload( void ) {
#ifdef SSQC
	if ( BaseGun_Reload() == TRUE ) {
	}
#else
	View_PlayAnimation( ANIM_P228_RELOAD );
#endif
}
