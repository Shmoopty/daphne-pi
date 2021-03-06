/*
 * ldp-combo.h
 *
 * Copyright (C) 2001 Matt Ownby
 *
 * This file is part of DAPHNE, a laserdisc arcade game emulator
 *
 * DAPHNE is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * DAPHNE is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
 */


// ldp-combo.h
// by Matt Ownby

#include "ldp.h"
#include "sony.h"
#include "ldp-vldp.h"

class combo : public ldp
{
public:
	combo();
	virtual ~combo() {};	// this keeps g++ happy
	bool init_player();
	void shutdown_player();
	bool search(char *);
	unsigned int play();
	void pause();
private:
	ldp_vldp m_vldp;	// our instance of a fake laserdisc player
	sony m_rldp;	// our instance of a real laserdisc player
};
