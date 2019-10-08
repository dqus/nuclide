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

/*QUAKED point_message (1 0 0) (-8 -8 -8) (8 8 8)
"message"       The message to display.
"radius"        The radius in which it will appear.

Client-side overlay/message that is projected in relation to its position
in 3D space.
Used for zoo and test maps in which less interactive overlays are desired.
*/

class point_message:CBaseEntity
{
	float radius;
	string message;
	void() point_message;
	virtual void(string, string) SpawnKey;
};

void point_message::SpawnKey(string strField, string strKey)
{
	switch (strField) {
		case "radius":
			radius = stof(strKey);
			break;
		case "message":
			message = strKey;
			break;
		case "origin":
			origin = stov( strKey );
			setorigin( this, origin );
			break;
		default:
			CBaseEntity::SpawnKey(strField, strKey);
	}
}

void point_message::point_message(void)
{
	radius = 512;
	message = "No message";
	Init();
}
