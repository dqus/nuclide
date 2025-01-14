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
	BASEFL_CHANGED_MODELINDEX,
	BASEFL_CHANGED_ORIGIN_X,
	BASEFL_CHANGED_ORIGIN_Y,
	BASEFL_CHANGED_ORIGIN_Z,
	BASEFL_CHANGED_ANGLES_X,
	BASEFL_CHANGED_ANGLES_Y,
	BASEFL_CHANGED_ANGLES_Z,
	BASEFL_CHANGED_VELOCITY_X,
	BASEFL_CHANGED_VELOCITY_Y,
	BASEFL_CHANGED_VELOCITY_Z,
	BASEFL_CHANGED_ANGULARVELOCITY,
	BASEFL_CHANGED_SIZE,
	BASEFL_CHANGED_FLAGS,
	BASEFL_CHANGED_SOLID,
	BASEFL_CHANGED_FRAME,
	BASEFL_CHANGED_SKIN,
	BASEFL_CHANGED_MOVETYPE,
	BASEFL_CHANGED_EFFECTS,
	BASEFL_CHANGED_SCALE,
};

/* NSEntity is the lowest, user accessible class.
   It's responsible for handling practically every entity in Nuclide.
	Try to avoid using the built-in 'entity' type unless you know exactly
   what you are doing.
*/
class NSEntity:NSTrigger
{
	bool m_bHidden;

	void(void) NSEntity;

	/* these are the real bounds, whereas .mins .maxs are affected by .scale */
	vector m_vecMins;
	vector m_vecMaxs;

	/* important spawn values */
	vector m_oldOrigin;
	vector m_oldAngle;
	string m_oldModel;
	float m_oldSolid;

	/* keep track of these variables */
	PREDICTED_VECTOR_N(origin);
	PREDICTED_VECTOR_N(angles);
	PREDICTED_FLOAT_N(modelindex);
	PREDICTED_VECTOR_N(size);
	PREDICTED_VECTOR_N(mins);
	PREDICTED_VECTOR_N(maxs);
	PREDICTED_FLOAT_N(solid);
	PREDICTED_FLOAT_N(movetype);
	PREDICTED_FLOAT_N(scale);
	PREDICTED_FLOAT_N(flags);
	PREDICTED_VECTOR_N(velocity);
	PREDICTED_VECTOR_N(avelocity);

	virtual void(void) Spawned;

#ifdef CLIENT
	virtual void(float,float) ReceiveEntity;
	virtual void(void) postdraw;
	virtual void(void) RendererRestarted;
	virtual void(void) OnRemoveEntity;
#endif

	/* overrides */
#ifdef SERVER
	virtual void(void) Respawn;
	virtual void(entity, string, string) Input;
	virtual void(float) Save;
	virtual void(string,string) Restore;
	virtual void(void) RestoreComplete;
#endif

#ifdef SERVER
	string m_parent;
	string m_parent_attachment;
	PREDICTED_FLOAT_N(frame);
	PREDICTED_FLOAT_N(skin);
	PREDICTED_FLOAT_N(effects);

	virtual void(void) EvaluateEntity;
	virtual float(entity, float) SendEntity;

	nonvirtual entity(void) GetParent;
	nonvirtual void(string) SetParent;
	nonvirtual void(string) SetParentAttachment;
	nonvirtual void(void) ClearParent;
	virtual void(void) ParentUpdate;

	/* some ents need this */
	nonvirtual void(void) RestoreAngles;
	nonvirtual void(void) ClearAngles;
#endif

	/* sets */
	nonvirtual void(float) SetEffects;
	nonvirtual void(float) SetFrame;
	nonvirtual void(float) SetSkin;
	nonvirtual void(float) SetScale;
	nonvirtual void(entity) SetOwner;
	nonvirtual void(vector) SetVelocity;
	nonvirtual void(void()) SetTouch;
	nonvirtual void(float) SetSendFlags;
	nonvirtual void(float) SetSolid;
	nonvirtual void(string) SetModel;
	nonvirtual void(float) SetModelindex;
	nonvirtual void(float) SetMovetype;
	nonvirtual void(float) SetGravity;
	nonvirtual void(vector) SetAngles;
	nonvirtual void(vector) SetAngularVelocity;
	nonvirtual void(vector) SetOrigin;
	nonvirtual void(vector, vector) SetSize;
	nonvirtual void(float) AddFlags;
	nonvirtual void(float) RemoveFlags;
	nonvirtual void(void()) SetThink;
	nonvirtual void(float) SetNextThink;
	nonvirtual void(void(void), float) ScheduleThink;

	/* gets */
	nonvirtual vector(void) GetSpawnOrigin;
	nonvirtual vector(void) GetSpawnAngles;
	nonvirtual string(void) GetSpawnModel;

	nonvirtual float(void) GetEffects;
	nonvirtual float(void) GetFrame;
	nonvirtual float(void) GetSkin;
	nonvirtual float(void) GetScale;
	nonvirtual entity(void) GetOwner;
	nonvirtual vector(void) GetVelocity;
	nonvirtual float(void) GetSolid;
	nonvirtual string(void) GetModel;
	nonvirtual float(void) GetModelindex;
	nonvirtual float(void) GetMovetype;
	nonvirtual float(void) GetGravity;
	nonvirtual vector(void) GetAngles;
	nonvirtual vector(void) GetAngularVelocity;
	nonvirtual vector(void) GetOrigin;
	nonvirtual vector(void) GetMins;
	nonvirtual vector(void) GetMaxs;
	nonvirtual vector(void) GetRealMins;
	nonvirtual vector(void) GetRealMaxs;
	nonvirtual vector(void) GetAbsoluteMins;
	nonvirtual vector(void) GetAbsoluteMaxs;
	nonvirtual float(void) GetFlags;
	nonvirtual float(void) GetNextThinkTime;
	nonvirtual bool(void) IsThinking;
	nonvirtual void(void) ReleaseThink;
	nonvirtual void(void) ClearVelocity;

	/* drawing related */
	nonvirtual void(void) Show;
	nonvirtual void(void) Hide;
	nonvirtual bool(void) IsHidden;

	/* this will not just hide an entity, it'll make it disappear from the game, but not deallocated it */
	nonvirtual void(void) Disappear;

	virtual void(string, string) SpawnKey;
	nonvirtual void(void) Destroy;
	nonvirtual void(void) UpdateBounds;

	/* useful methods, (some) based on GMod's API */
	nonvirtual float(void) EntIndex;
	nonvirtual void(void) DropToFloor;
	nonvirtual vector(void) GetForward;
	nonvirtual vector(void) GetRight;
	nonvirtual vector(void) GetUp;
	nonvirtual vector(void) WorldSpaceCenter;
	nonvirtual float(void) WaterLevel;
	nonvirtual bool(entity) Visible;
	nonvirtual bool(vector) VisibleVec;
	nonvirtual bool(float) HasSpawnFlags;
	nonvirtual bool(void) IsOnGround;
	nonvirtual entity(void) GetGroundEntity;
	nonvirtual bool(void) CreatedByMap;
	nonvirtual bool(entity) WithinBounds;

	/* useful methods, (some) based on Doom 3's API */
	nonvirtual bool(string, float, float, bool) StartSound;
	nonvirtual bool(string, float, bool) StartSoundDef;
	nonvirtual void(float, bool) StopSound;

	nonvirtual void(void) HandleThink;

	virtual void(void) OnRemoveEntity;
	virtual void(void) MakeStatic;
};
