/***
*
*	Copyright (c) 2016-2019 Marco 'eukara' Hladik. All rights reserved.
*
*	See the file LICENSE attached with the sources for usage details.
*
****/

.int iMag_AUG;

// Weapon Info
weaponinfo_t wptAUG = {
	WEAPON_AUG, 		// Identifier
	SLOT_PRIMARY,		// Slot
	3500, 				// Price
	CALIBER_762MM, 		// Caliber ID
	0.96, 				// Max Player Speed
	1, 					// Bullets Per Shot
	30, 				// Clip/MagSize
	32, 				// Damage Per Bullet
	2, 					// Penetration Multiplier
	8192, 				// Bullet Range
	0.96, 				// Range Modifier
	TYPE_AUTO,			// Firing Type
	0.0825, 				// Attack-Delay
	3.3, 				// Reload-Delay
	iAmmo_762MM, 		// Caliber Pointer
	iMag_AUG, 			// Clip Pointer
	215,				// Accuracy Divisor
	0.3,				// Accuracy Offset
	1.0,				// Max Inaccuracy
	3,					// Minimum Crosshair Distance
	3,					// Crosshair Movement Delta
	1.4,				// Armor penetration ratio
	ATYPE_RIFLE,		// Animation Type
	SHELL_RIFLE
};

// Anim Table
enum {
	ANIM_AUG_IDLE,
	ANIM_AUG_RELOAD,
	ANIM_AUG_DRAW,
	ANIM_AUG_SHOOT1,
	ANIM_AUG_SHOOT2,
	ANIM_AUG_SHOOT3
};

void WeaponAUG_Draw( void ) {
#ifdef SSQC
	BaseGun_Draw();
#else
	View_PlayAnimation( ANIM_AUG_DRAW );
#endif
}

void WeaponAUG_PrimaryFire( void ) {
#ifdef SSQC
	if ( BaseGun_PrimaryFire() == TRUE ) {
		sound( self, CHAN_WEAPON, "weapons/aug-1.wav", 1, ATTN_NORM );
		
		if ( self.viewzoom != 1.0 ) {
			self.fAttackFinished = time + 0.135;
		}
	}
#else
	int iRand = (int)floor( random( 1, 4 ) );
	if ( iRand == 1 ) {
		View_PlayAnimation( ANIM_AUG_SHOOT1 );
	} else if ( iRand == 2 ) {
		View_PlayAnimation( ANIM_AUG_SHOOT2 );
	} else {
		View_PlayAnimation( ANIM_AUG_SHOOT3 );
	}
	
	BaseGun_ShotMultiplierHandle( 1 );
#endif
}

void WeaponAUG_SecondaryFire( void ) {
#ifdef SSQC
	if ( self.viewzoom != 1.0 ) {
		self.viewzoom = 1.0;
	} else {
		self.viewzoom = 0.6;
	}

	self.fAttackFinished = time + 0.5;
#endif
}

void WeaponAUG_Reload( void ) {
#ifdef SSQC
	if ( BaseGun_Reload() == TRUE ) {
		// Play Sound
	}
#else
	View_PlayAnimation( ANIM_AUG_RELOAD );
#endif
}
