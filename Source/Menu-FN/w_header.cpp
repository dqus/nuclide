/***
*
*	Copyright (c) 2016-2019 Marco 'eukara' Hladik. All rights reserved.
*
*	See the file LICENSE attached with the sources for usage details.
*
****/

class CHeader:CWidget
{
	int m_header;
	float m_lerp;
	int m_start_x;
	int m_start_y;
	int m_end_x;
	int m_end_y;
	int m_start_w;
	int m_start_h;
	int m_end_w;
	int m_end_h;
	int m_visible;

	virtual void() m_execute = 0;

	virtual void() Draw;
	virtual void(int x1, int y1, int x2, int y2) SetStartEndPos;
	virtual void(int x1, int y1, int x2, int y2) SetStartEndSize;
	virtual void(int i) SetHeader;
};

void CHeader::Draw(void)
{
	int pos[2];
	int size[2];

	if (m_visible == FALSE) {
		return;
	}

	pos[0] = g_menuofs[0] + lerp(m_start_x, m_end_x, m_lerp);
	pos[1] = g_menuofs[1] + lerp(m_start_y, m_end_y, m_lerp);
	
	size[0] = lerp(m_start_w, m_end_w, m_lerp);
	size[1] = lerp(m_start_h, m_end_h, m_lerp);

	drawpic([pos[0],pos[1]], g_bmp[m_header],[size[0],size[1]], [1,1,1], 1.0f, 1);

#if 0
	m_lerp += frametime * 0.25;
#else
	m_lerp += frametime * 8;
#endif

	m_lerp = bound(0.0f, m_lerp, 1.0f);

	if (m_lerp == 1.0f) {
		if (m_visible == TRUE) {
			m_visible = FALSE;
			
			if (m_execute) {
				m_execute();
			}
		}
	}
}

void CHeader::SetHeader(int i)
{
	m_header = i;
}

void CHeader::SetExecute(void() vFunc)
{
	m_execute = vFunc;
}

void CHeader::SetStartEndPos(int x1, int y1, int x2, int y2)
{
	m_start_x = x1;
	m_start_y = y1;
	m_end_x = x2;
	m_end_y = y2;
}

void CHeader::SetStartEndSize(int x1, int y1, int x2, int y2)
{
	m_start_w = x1;
	m_start_h = y1;
	m_end_w = x2;
	m_end_h = y2;
}

CHeader header;
