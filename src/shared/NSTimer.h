/*
 * Copyright (c) 2022 Vera Visions LLC.
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

class
NSTimer:NSEntity
{
	entity m_eReceiver;
	virtual void(void) m_vFunc = 0;
	float m_flTime;
	bool m_bRepeats;
	
	void(void) NSTimer;

	virtual void(void) _TimerThink;
	virtual void(void) _TempTimerThink;

	/* creates and sets up a new timer, starts immediately */
	static NSTimer(entity, void(), float, bool) ScheduleTimer;
	/* self garbage collecting version of the above */
	static NSTimer(entity, void(), float, bool) TemporaryTimer;

	/* when you want to set up a timer ahead of time, but only run it manually */
	virtual void(void) RunTimer;
	static NSTimer(entity, void(), float, bool) SetupTimer;
};