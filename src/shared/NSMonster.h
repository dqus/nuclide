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

enumflags
{
	MONFL_CHANGED_ORIGIN_X,
	MONFL_CHANGED_ORIGIN_Y,
	MONFL_CHANGED_ORIGIN_Z,
	MONFL_CHANGED_ANGLES_X,
	MONFL_CHANGED_ANGLES_Y,
	MONFL_CHANGED_ANGLES_Z,
	MONFL_CHANGED_MODELINDEX,
	MONFL_CHANGED_SIZE,
	MONFL_CHANGED_FLAGS,
	MONFL_CHANGED_SOLID,
	MONFL_CHANGED_FRAME,
	MONFL_CHANGED_SKIN,
	MONFL_CHANGED_MOVETYPE,
	MONFL_CHANGED_EFFECTS,
	MONFL_CHANGED_BODY,
	MONFL_CHANGED_SCALE,
	MONFL_CHANGED_VELOCITY,
	MONFL_CHANGED_RENDERCOLOR,
	MONFL_CHANGED_RENDERAMT,
	MONFL_CHANGED_RENDERMODE,
};

typedef enum {
	ACT_RESET = 0,
	ACT_IDLE = 1i,
	ACT_GUARD,
	ACT_WALK,
	ACT_RUN,
	ACT_FLY,
	ACT_SWIM,
	ACT_HOP,
	ACT_LEAP,
	ACT_FALL,
	ACT_LAND,
	ACT_STRAFE_LEFT,
	ACT_STRAFE_RIGHT,
	ACT_ROLL_LEFT,
	ACT_ROLL_RIGHT,
	ACT_TURN_LEFT,
	ACT_TURN_RIGHT,
	ACT_CROUCH,
	ACT_CROUCHIDLE,	
	ACT_STAND,
	ACT_USE,
	ACT_SIGNAL1,
	ACT_SIGNAL2,
	ACT_SIGNAL3,
	ACT_TWITCH,
	ACT_COWER,
	ACT_SMALL_FLINCH,
	ACT_BIG_FLINCH,
	ACT_RANGE_ATTACK1,
	ACT_RANGE_ATTACK2,
	ACT_MELEE_ATTACK1,
	ACT_MELEE_ATTACK2,
	ACT_RELOAD,
	ACT_ARM,
	ACT_DISARM,
	ACT_EAT,
	ACT_DIESIMPLE,
	ACT_DIEBACKWARD,
	ACT_DIEFORWARD,
	ACT_DIEVIOLENT,
	ACT_BARNACLE_HIT,
	ACT_BARNACLE_PULL,
	ACT_BARNACLE_CHOMP,
	ACT_BARNACLE_CHEW,
	ACT_SLEEP,
	ACT_INSPECT_FLOOR,
	ACT_INSPECT_WALL,
	ACT_IDLE_ANGRY,
	ACT_WALK_HURT,
	ACT_RUN_HURT,
	ACT_HOVER,
	ACT_GLIDE,
	ACT_FLY_LEFT,
	ACT_FLY_RIGHT,
	ACT_DETECT_SCENT,
	ACT_SNIFF,
	ACT_BITE,
	ACT_THREAT_DISPLAY,
	ACT_FEAR_DISPLAY,
	ACT_EXCITED,
	ACT_SPECIAL_ATTACK1,
	ACT_SPECIAL_ATTACK2,	
	ACT_COMBAT_IDLE,
	ACT_WALK_SCARED,
	ACT_RUN_SCARED,
	ACT_VICTORY_DANCE,
	ACT_DIE_HEADSHOT,
	ACT_DIE_CHESTSHOT,
	ACT_DIE_GUTSHOT,
	ACT_DIE_BACKSHOT,
	ACT_FLINCH_HEAD,
	ACT_FLINCH_CHEST,
	ACT_FLINCH_STOMACH,
	ACT_FLINCH_LEFTARM,
	ACT_FLINCH_RIGHTARM,
	ACT_FLINCH_LEFTLEG,
	ACT_FLINCH_RIGHTLEG,
} monster_activity_t;

/* monster flags, these are defined by the level designers */
typedef enumflags
{
	MSF_WAITTILLSEEN,
	MSF_GAG,
	MSF_MONSTERCLIP,
	MSF_RESERVED1,
	MSF_PRISONER,
	MSF_RESERVED2,
	MSF_IGNOREPLAYER,
	MSF_WAITFORSCRIPT,
	MSF_PREDISASTER,
	MSF_FADECORPSE,
	MSF_MULTIPLAYER,
	MSF_FALLING,
	MSF_HORDE
} monsterFlag_t;

/* movement states */
typedef enum
{
	MONSTER_IDLE,
	MONSTER_ALERT,
	MONSTER_FOLLOWING,
	MONSTER_CHASING,
	MONSTER_AIMING,
	MONSTER_DEAD,
	MONSTER_GIBBED
} monsterState_t;

/* scripted sequence states */
typedef enum
{
	SEQUENCESTATE_NONE,
	SEQUENCESTATE_IDLE,
	SEQUENCESTATE_ACTIVE,
	SEQUENCESTATE_ENDING
} sequenceState_t;

/* alliance state */
typedef enum
{
	MAL_FRIEND, /* friendly towards the player */
	MAL_ENEMY,  /* unfriendly towards the player */
	MAL_ALIEN,  /* unfriendly towards anyone but themselves */
	MAL_ROGUE   /* no allies, not even amongst themselves */
} allianceState_t;

typedef enum
{
	MOVESTATE_IDLE,
	MOVESTATE_WALK,
	MOVESTATE_RUN
} movementState_t;

/* These numerations involve the m_iTriggerCondition attribute.
 * Basically these conditions are being checked and triggered depending on what
 * it's set to. If any of those checks are successful, we trigger our target
 * under the m_strTriggerTarget attribute. */
typedef enum
{
	MTRIG_NONE,					/* nothing */
	MTRIG_SEEPLAYER_ANGRY,		/* we see an enemy player, that we want to harm */
	MTRIG_PAIN,					/* taken damage */ 
	MTRIG_HALFHEALTH,			/* lost half of our base_health */
	MTRIG_DEATH,				/* we have died. */
	MTRIG_SQUADMEMBERDEAD,		/* a squad member died */
	MTRIG_SQUADLEADERDEAD,		/* the squad leader died */
	MTRIG_HEARNOISE,			/* we hear some noise around the world. */
	MTRIG_HEARENEMYPLAYER,		/* we hear a player we are enemies with */
	MTRIG_HEARWEAPONS,			/* we hear weapons being fired */
	MTRIG_SEEPLAYER,			/* we see a player, don't have to be angry at him. */
	MTRIG_SEEPLAYER_RELAXED,	/* we see a player and we're currently attacking anything */
} triggerCondition_t;

/* FIXME: I'd like to move this into NSMonster, but our current IsFriend()
 * check is currently only checking on a .takedamage basis. */
.int m_iAlliance;

class NSMonster:NSNavAI
{
#ifdef SERVER
	entity m_ssLast;
	vector oldnet_velocity;
	float m_flPitch;
	int m_iFlags;
	vector base_mins;
	vector base_maxs;
	float base_health;

	/* sequences */
	string m_strRouteEnded;
	int m_iSequenceRemove;
	int m_iSequenceState;
	float m_flSequenceEnd;
	float m_flSequenceSpeed;
	vector m_vecSequenceAngle;
	int m_iSequenceFlags;
	movementState_t m_iMoveState;

	int m_iTriggerCondition;
	string m_strTriggerTarget;

	/* model events */
	float m_flBaseTime;

	/* attack/alliance system */
	entity m_eEnemy;
	float m_flAttackThink;
	monsterState_t m_iMState;
	monsterState_t m_iOldMState;
	vector m_vecLKPos; /* last-known pos */

#endif

	void(void) NSMonster;

#ifdef SERVER	
	/* overrides */
	virtual void(float) Save;
	virtual void(string,string) Restore;

	virtual void(entity) Touch;
	virtual void(void) Hide;
	virtual void(void) Respawn;
	virtual void(void) Pain;
	virtual void(void) Death;
	virtual void(void) Physics;
	virtual void(void) RunAI;
	virtual void(void) IdleNoise;
	virtual void(void) FallNoise;
	virtual void(void) Gib;
	virtual void(string) Sound;
	virtual void(string, string) SpawnKey;

	virtual bool(void) IsAlive;
	virtual bool(int) IsFriend;

	/* see/hear subsystem */
	float m_flSeeTime;
	virtual void(void) SeeThink;
	virtual float(void) SeeFOV;

	/* reactions */
	virtual void(void) AlertNearby;

	/* movement */
	virtual float(void) GetWalkSpeed;
	virtual float(void) GetChaseSpeed;
	virtual float(void) GetRunSpeed;

	/* attack system */
	virtual void(void) AttackDraw;
	virtual void(void) AttackHolster;
	virtual void(void) AttackThink;
	virtual int(void) AttackMelee;
	virtual int(void) AttackRanged;

	virtual float(void) MeleeMaxDistance;
	virtual bool(void) MeleeCondition;

	nonvirtual bool(entity enemy) IsValidEnemy;

	/* sequences */
	virtual void(void) FreeState;
	virtual void(void) FreeStateMoved;
	virtual void(void) RouteEnded;
	virtual void(void) WalkRoute;
	nonvirtual int(void) GetSequenceState;
	nonvirtual bool(void) InSequence;

	/* animation cycles */
	float m_flAnimTime;
	virtual int(void) AnimIdle;
	virtual int(void) AnimWalk;
	virtual int(void) AnimRun;
	virtual void(float) AnimPlay;
	virtual void(void) AnimationUpdate;
	nonvirtual bool(void) InAnimation;

	/* states */
	virtual void(monsterState_t, monsterState_t) StateChanged;
	nonvirtual void(monsterState_t) SetState;
	nonvirtual monsterState_t(void) GetState;

	/* TriggerTarget/Condition */
	nonvirtual int(void) GetTriggerCondition;
	virtual void(void) TriggerTargets;

	virtual float(entity, float) SendEntity;
#else
	virtual void(void) customphysics;
	virtual float(void) predraw;
	virtual void(float,float) ReceiveEntity;
#endif
};

#ifdef CLIENT
string Sentences_GetSamples(string);
string Sentences_ProcessSample(string);
void NSMonster_ReadEntity(bool);
#else
void NSMonster_AlertEnemyAlliance(vector pos, float radius, int alliance);
entity NSMonster_FindClosestPlayer(entity);
#endif
