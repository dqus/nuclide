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

typedef enumflags
{
	DMG_GENERIC,
	DMG_CRUSH,
	DMG_BULLET,
	DMG_SLASH,
	DMG_FREEZE,
	DMG_BURN,
	DMG_VEHICLE,
	DMG_FALL,
	DMG_EXPLODE,
	DMG_BLUNT,
	DMG_ELECTRO,
	DMG_SOUND,
	DMG_ENERGYBEAM,
	DMG_GIB_NEVER,
	DMG_GIB_ALWAYS,
	DMG_DROWN,
	DMG_PARALYZE,
	DMG_NERVEGAS,
	DMG_POISON,
	DMG_RADIATION,
	DMG_DROWNRECOVER,
	DMG_CHEMICAL,
	DMG_SLOWBURN,
	DMG_SLOWFREEZE,
	DMG_SKIP_ARMOR,
	DMG_SKIP_RAGDOLL
} damageType_t;

#define DMG_ACID DMG_CHEMICAL
