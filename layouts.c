void
grid(Monitor *m) {
	unsigned int i, n, cx, cy, cw, ch, aw, ah, cols, rows;
	Client *c;

	int gapw = 16, gaph = 16;

	for(n = 0, c = nexttiled(m->clients); c; c = nexttiled(c->next))
		n++;

	/* grid dimensions */
	for(rows = 0; rows <= n/2; rows++)
		if(rows*rows >= n)
			break;
	cols = (rows && (rows - 1) * rows >= n) ? rows - 1 : rows;

	/* window geoms (cell height/width) */
	ch = m->wh / (rows ? rows : 1);
	cw = m->ww / (cols ? cols : 1);
	for(i = 0, c = nexttiled(m->clients); c; c = nexttiled(c->next)) {
		cx = m->wx + (i / rows) * cw;
		cy = m->wy + (i % rows) * ch;
		/* adjust height/width of last row/column's windows */
		ah = ((i + 1) % rows == 0) ? m->wh - ch * rows : 0;
		aw = (i >= rows * (cols - 1)) ? m->ww - cw * cols : 0;
		/* igorg:  add gaps: gapw and gaph */
		resize(c, cx + gapw, cy + gaph, cw - 2 * c->bw + aw - 2 * gapw, ch - 2 * c->bw + ah - 2 * gaph, False);
		i++;
	}
}

void
tcl(Monitor * m)
{
	int x, y, h, w, mw, sw, bdw;
	unsigned int i, n;
	Client * c;

	for (n = 0, c = nexttiled(m->clients); c;
	        c = nexttiled(c->next), n++);

	if (n == 0)
		return;

	c = nexttiled(m->clients);

	mw = m->mfact * m->ww;
	sw = (m->ww - mw) / 2;
	bdw = (2 * c->bw);
	resize(c,
	       n < 3 ? m->wx : m->wx + sw,
	       m->wy,
	       n == 1 ? m->ww - bdw : mw - bdw,
	       m->wh - bdw,
	       False);

	if (--n == 0)
		return;

	w = (m->ww - mw) / ((n > 1) + 1);
	c = nexttiled(c->next);

	if (n > 1)
	{
		x = m->wx + ((n > 1) ? mw + sw : mw);
		y = m->wy;
		h = m->wh / (n / 2);

		if (h < bh)
			h = m->wh;

		for (i = 0; c && i < n / 2; c = nexttiled(c->next), i++)
		{
			resize(c,
			       x,
			       y,
			       w - bdw,
			       (i + 1 == n / 2) ? m->wy + m->wh - y - bdw : h - bdw,
			       False);

			if (h != m->wh)
				y = c->y + HEIGHT(c);
		}
	}

	x = (n + 1 / 2) == 1 ? mw : m->wx;
	y = m->wy;
	h = m->wh / ((n + 1) / 2);

	if (h < bh)
		h = m->wh;

	for (i = 0; c; c = nexttiled(c->next), i++)
	{
		resize(c,
		       x,
		       y,
		       (i + 1 == (n + 1) / 2) ? w - bdw : w - bdw,
		       (i + 1 == (n + 1) / 2) ? m->wy + m->wh - y - bdw : h - bdw,
		       False);

		if (h != m->wh)
			y = c->y + HEIGHT(c);
	}
}

void
tcl_always(Monitor * m)
{
	int x, y, h, w, mw, sw, bdw;
	unsigned int i, n;
	Client * c;
	int right_n, left_n;

	for (n = 0, c = nexttiled(m->clients); c;
	        c = nexttiled(c->next), n++);

	if (n == 0)
		return;

	// position master window
	c = nexttiled(m->clients);

	mw = m->mfact * m->ww;
	sw = (m->ww - mw) / 2;
	bdw = (2 * c->bw);
	resize(c,
	       m->wx + sw,
	       m->wy,
	       mw - bdw,
	       m->wh - bdw,
	       False);

	if (--n == 0)
		return;

	// right stack
	right_n = (n + 1) / 2;  // round up for right stack
	left_n = n - right_n;   // so the first stack window will be on the right

	x = m->wx + sw + mw;
	w = (m->ww - mw) / 2;
	y = m->wy;
	h = m->wh / right_n;

	if (h < bh)
		h = m->wh; // if there are too many windows, show one with full height

	for (c = nexttiled(c->next), i = 0; c && i < right_n; c = nexttiled(c->next), ++i)
	{
		bdw = (2 * c->bw);
		resize(c,
		       x,
		       y,
		       w - bdw,
		       h - bdw,
		       False);

		if (h != m->wh)
			y = c->y + HEIGHT(c);
	}

	if (left_n == 0)
		return;

	// left stack
	x = m->wx;
	w = (m->ww - mw) / 2;
	y = m->wy;
	h = m->wh / left_n;

	if (h < bh)
		h = m->wh; // if there are too many windows, show one with full height

	for (; c; c = nexttiled(c->next))
	{
		bdw = (2 * c->bw);
		resize(c,
		       x,
		       y,
		       w - bdw,
		       h - bdw,
		       False);

		if (h != m->wh)
			y = c->y + HEIGHT(c);
	}
}
