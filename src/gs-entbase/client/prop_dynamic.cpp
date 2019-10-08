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


/*QUAKED prop_dynamic (1 0 0) (-8 -8 -8) (8 8 8)
"model"       Model file that will be displayed by the entity.
"modelscale"  Scale modifier of the model. Default is '1'.
"angles"      Sets the pitch, yaw and roll angles of the model.
"_cs"         Toggles if the prop casts a shadow or not.

Client-side decorative model entity.
*/


class prop_dynamic:CBaseEntity {
	virtual void() Init;
	virtual void() PhysicsFrame;
	/*virtual float() predraw;*/
	virtual void(string, string) SpawnKey;
};

void prop_dynamic::SpawnKey(string strField, string strKey)
{
	switch (strField) {
		case "modelscale":
			scale = stof(strKey);
			break;
		case "angle":
			angles[1] = stof(strKey);
			break;
		default:
			CBaseEntity::SpawnKey(strField, strKey);
	}
}

/*float prop_dynamic::predraw(void)
{
	if (checkpvs(viewClient.vecPlayerOrigin, this) == TRUE) {
		addentity(this);
	}
	return PREDRAW_NEXT;
}*/

void prop_dynamic::Init(void)
{
	CBaseEntity::Init();

	precache_model(model);
	setmodel(this, model);
	setorigin(this, origin);
	setsize(this, mins * scale, maxs * scale);
	drawmask = MASK_ENGINE;
}

void prop_dynamic::PhysicsFrame(void)
{
	//angles[1] += clframetime * 60;
}
