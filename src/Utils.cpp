/*
	zbnt/server-shared
	Copyright (C) 2019 Oscar R.

	This program is free software: you can redistribute it and/or modify
	it under the terms of the GNU General Public License as published by
	the Free Software Foundation, either version 3 of the License, or
	(at your option) any later version.

	This program is distributed in the hope that it will be useful,
	but WITHOUT ANY WARRANTY; without even the implied warranty of
	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
	GNU General Public License for more details.

	You should have received a copy of the GNU General Public License
	along with this program.  If not, see <https://www.gnu.org/licenses/>.
*/

#include <Utils.hpp>

void writeMessage(QIODevice *dev, MessageID msgID, const QByteArray &value)
{
	dev->write(MSG_MAGIC_IDENTIFIER, 4);
	writeAsBytes<uint16_t>(dev, msgID);
	writeAsBytes<uint16_t>(dev, value.size());
	dev->write(value);
}

void buildMessage(QByteArray &array, MessageID msgID, const QByteArray &value)
{
	array.append(MSG_MAGIC_IDENTIFIER, 4);
	appendAsBytes<uint16_t>(array, msgID);
	appendAsBytes<uint16_t>(array, value.size());
	array.append(value);
}

void setDeviceProperty(QByteArray &array, uint8_t devID, PropertyID propID, const QByteArray &value)
{
	array.append(MSG_MAGIC_IDENTIFIER, 4);
	appendAsBytes<uint16_t>(array, MSG_ID_SET_PROPERTY);
	appendAsBytes<uint16_t>(array, 3 + value.size());
	appendAsBytes<uint8_t>(array, devID);
	appendAsBytes<uint16_t>(array, propID);
	array.append(value);
}