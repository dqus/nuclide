/*
OpenCS Project
Copyright (C) 2015 Marco "eukara" Hladik

This program is free software; you can redistribute it and/or
modify it under the terms of the GNU General Public License
as published by the Free Software Foundation; either version 2
of the License, or (at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.

See the GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program; if not, write to the Free Software
Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.
*/

enum {
	BUY_BOTH,
	BUY_CT,
	BUY_T,
	BUY_NEITHER
};

// Checks if it is possible for players to buy anything
float Rules_BuyingPossible( void ) {
	if ( fGameState == GAME_ACTIVE ) {
		if ( ( ( cvar( "mp_roundtime" ) * 60 ) - fGameTime ) > cvar( "mp_buytime" ) ) {
			centerprint( self, sprintf( "%d seconds have passed...\nYou can't buy anything now!", cvar( "mp_buytime" ) ) );
			self.fAttackFinished = time + 1.0;
			return FALSE;
		}
	}
	
	if ( self.team == TEAM_VIP ) {
		centerprint( self, "You are the VIP...\nYou can't buy anything!\n" );
		self.fAttackFinished = time + 1.0;
		return FALSE;
	}
	
	if ( iBuyRestriction == BUY_NEITHER ) {
		centerprint( self, "Sorry, you aren't meant\nto be buying anything.\n" );
		self.fAttackFinished = time + 1.0;
		return FALSE;
	}
	
	if ( iBuyRestriction != BUY_BOTH ) {
		if ( iBuyRestriction == BUY_CT && self.team == TEAM_T ) {
			centerprint( self, "Terrorists aren't allowed to\nbuy anything on this map!\n" );
			self.fAttackFinished = time + 1.0;
			return FALSE;
		} else if ( iBuyRestriction == BUY_T && self.team == TEAM_CT ) {
			centerprint( self, "CTs aren't allowed to buy\nanything on this map!\n" );
			self.fAttackFinished = time + 1.0;
			return FALSE;
		}
	}
	
	return TRUE;
}

// Loop through all players and respawn them
void Rules_Restart( void ) {
	
	iHostagesRescued = 0;
	
	entity eFind = findchain( classname, "player" );
	entity eOld = self;
	
	while ( eFind ) {
		
		self = eFind;
		
		if ( self.health > 0 ) {
			Spawn_RespawnClient( self.team );
		} else {
			Spawn_CreateClient( self.fCharModel );
		}
		
		Money_GiveTeamReward();
		
		eFind = eFind.chain;
	}
	
	self = eOld;
	
	// Select a random Terrorist for the bomb thing
	if ( iBombZones > 0 ) {
		int iRandomT = ceil( random() * iAlivePlayers_T );
		int iPickT = 0;
		
		eFind = findchain( classname, "player" );
		while ( eFind ) {
			
			if ( eFind.classname == "player" && eFind.team == TEAM_T ) {
				iPickT++;
				
				if ( iPickT == iRandomT ) {
					eOld = self;
					self = eFind;
					Weapon_AddItem( WEAPON_C4BOMB );
					self = eOld;
				}
			}
			
			eFind = eFind.chain;
		}
	} 
	
	// If there is a VIP, select a random CT to be it
	if ( iVIPZones > 0 ) {
		int iRandomCT = ceil( random() * iAlivePlayers_CT );
		int iPickCT = 0;

		eFind = findchain( classname, "player" );
		while ( eFind ) {
			
			if ( eFind.classname == "player" && eFind.team == TEAM_CT ) {
				iPickCT++;
				
				if ( iPickCT == iRandomCT ) {
					eOld = self;
					self = eFind;
					self.team = TEAM_VIP;
					Spawn_RespawnClient( self.team );
					self = eOld;
				}
			}
			
			eFind = eFind.chain;
		}
	}
	
	// Respawn all the entities
	eFind = findchainfloat( fRespawns , TRUE );
	eOld = self;
	while ( eFind ) {
		
		self = eFind;
		Entities_Respawn();
		
		eFind = eFind.chain;
	}
	self = eOld;
	
	Timer_Begin( cvar( "mp_freezetime" ), GAME_FREEZE );
	Money_ResetTeamReward();
}

// This can happen whenever an objective is complete or time is up
void Rules_RoundOver( int iTeamWon, int iMoneyReward ) {
	
	if ( fGameState != GAME_ACTIVE ) {
		return;
	}
	
	if ( iTeamWon == TEAM_T ) {
		Radio_BroadcastMessage( RADIO_TERWIN );
		iWon_T++;
	} else if ( iTeamWon == TEAM_CT ) {
		Radio_BroadcastMessage( RADIO_CTWIN );
		iWon_CT++;
	} else {
		Radio_BroadcastMessage( RADIO_ROUNDDRAW );
	}
	Money_QueTeamReward( iTeamWon, iMoneyReward );
	Timer_Begin( 5, GAME_END); // Round is over, 5 seconds til a new round starts
}

// Whenever mp_roundtime was being counted down to 0
void Rules_TimeOver( void ) {
	if ( iVIPZones > 0 ) {
		Rules_RoundOver( TEAM_T, 3250 );
	} else if ( iBombZones > 0 ) {
		Rules_RoundOver( TEAM_CT, 3250 );
	} else if ( iHostagesMax > 0 ) {
		// TODO: Broadcast_Print: Hostages have not been rescued!
		Rules_RoundOver( TEAM_T, 3250 );
	} else {
		Rules_RoundOver( 0, 0 );
	}
}

/*
=================
SPAWN: info_map_parameters

Let's map authors decide who can buy stuff and who CAN'T.
Also allows people to set the bomb placing radius incase you want to use info_bomb_target.
=================
*/
.float buying;
void info_map_parameters( void ) {
	if ( !self.buying ) {
		self.buying = BUY_BOTH;
	} else {
		iBuyRestriction = self.buying;
	}
}