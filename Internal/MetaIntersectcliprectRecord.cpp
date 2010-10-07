/* META_INTERSECTCLIPRECT record implementation.

   Copyright (C) 2010 rel-eng

   This file is part of QWmfPlugin.

   This program is free software; you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation; either version 3 of the License, or
   (at your option) any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program.  If not, see <http://www.gnu.org/licenses/>.  */

#include "MetaIntersectcliprectRecord.h"

#include "Utils/IOUtils.h"

#include <stdexcept>

MetaIntersectcliprectRecord::MetaIntersectcliprectRecord() : MetafileRecord(7, META_INTERSECTCLIPRECT), bottom(0), right(0), top(0), left(0)
{
}

MetaIntersectcliprectRecord::MetaIntersectcliprectRecord(qint16 bottom, qint16 right, qint16 top, qint16 left) : MetafileRecord(7, META_INTERSECTCLIPRECT), bottom(bottom), right(right), top(top), left(left)
{
}

MetaIntersectcliprectRecord::MetaIntersectcliprectRecord(QIODevice &device) : MetafileRecord(device)
{
    if((this->getRecordFunction() & 0x00FF) != (META_INTERSECTCLIPRECT & 0x00FF))
    {
        throw std::runtime_error("Not a META_INTERSECTCLIPRECT record");
    }
    this->bottom = readSignedWord(device);
    this->right = readSignedWord(device);
    this->top = readSignedWord(device);
    this->left = readSignedWord(device);
}

MetaIntersectcliprectRecord::MetaIntersectcliprectRecord(const MetaIntersectcliprectRecord &rhs) : MetafileRecord(rhs), bottom(rhs.bottom), right(rhs.right), top(rhs.top), left(rhs.left)
{
}

MetaIntersectcliprectRecord::~MetaIntersectcliprectRecord()
{
}

MetaIntersectcliprectRecord & MetaIntersectcliprectRecord::operator =(const MetaIntersectcliprectRecord &rhs)
{
    if (this != &rhs)
    {
        MetafileRecord::operator =(rhs);
        this->bottom = rhs.bottom;
        this->right = rhs.right;
        this->top = rhs.top;
        this->left = rhs.left;
    }
    return *this;
}

QRect MetaIntersectcliprectRecord::getRect() const
{
    return QRect(QPoint(this->left, this->top), QPoint(this->right, this->bottom));
}
