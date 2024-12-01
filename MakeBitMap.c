/* asm */

MakeBitMap(b,depth,width,height)
	register struct BitMap *b; LONG width, height, depth;
{	register short i, success=TRUE; PLANEPTR AllocRaster();

	if (!b) return FALSE;
	for (i=0; i<depth; i++) b->Planes[i] = NULL;	/* set all planes = nonexistant */
	InitBitMap(b,depth,width,height);				/* initialize map */

	for (i=0; i<depth && success; i++)				/* allocate all planes */
	{	if (!(b->Planes[i] = AllocRaster(width,height)) ) success = FALSE;  }
	if (!success) UnMakeBitMap(b);					/* if failure, de-allocate */

	return success;									/* return TRUE or FALSE */
}

/* de-allocate the rasters for this bit map */

UnMakeBitMap(b) register struct BitMap *b;
{	register short i;

	for (i=0; i<b->Depth; i++)						/* for each plane */
	{	if (b->Planes[i])							/* if that plane exists */
		{	FreeRaster(b->Planes[i],b->BytesPerRow,b->Rows);	/* free it */
			b->Planes[i] = NULL;					/* mark as free */
		}
		b->Depth = 0;								/* mark bitmap as empty */
	}
}
