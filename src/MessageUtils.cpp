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

#include <MessageUtils.hpp>

void writeMessage(QIODevice *dev, MessageID msgID, const QByteArray &value)
{
	dev->write(MSG_MAGIC_IDENTIFIER, 4);

	if(value.size() < 65536)
	{
		writeAsBytes<uint16_t>(dev, msgID);
		writeAsBytes<uint16_t>(dev, value.size());
	}
	else
	{
		writeAsBytes<uint16_t>(dev, MSG_ID_EXTENDED);
		writeAsBytes<uint16_t>(dev, msgID);
		writeAsBytes<uint32_t>(dev, value.size());
	}

	dev->write(value);
}

void buildMessage(QByteArray &array, MessageID msgID, const QByteArray &value)
{
	array.append(MSG_MAGIC_IDENTIFIER, 4);

	if(value.size() < 65536)
	{
		appendAsBytes<uint16_t>(array, msgID);
		appendAsBytes<uint16_t>(array, value.size());
	}
	else
	{
		appendAsBytes<uint16_t>(array, MSG_ID_EXTENDED);
		appendAsBytes<uint16_t>(array, msgID);
		appendAsBytes<uint32_t>(array, value.size());
	}

	array.append(value);
}

void setDeviceProperty(QByteArray &array, uint8_t devID, PropertyID propID, const QByteArray &value)
{
	array.append(MSG_MAGIC_IDENTIFIER, 4);

	if(value.size() + 3 < 65536)
	{
		appendAsBytes<uint16_t>(array, MSG_ID_SET_PROPERTY);
		appendAsBytes<uint16_t>(array, 3 + value.size());
		appendAsBytes<uint8_t>(array, devID);
		appendAsBytes<uint16_t>(array, propID);
	}
	else
	{
		appendAsBytes<uint16_t>(array, MSG_ID_EXTENDED);
		appendAsBytes<uint16_t>(array, MSG_ID_SET_PROPERTY);
		appendAsBytes<uint32_t>(array, 3 + value.size());
		appendAsBytes<uint8_t>(array, devID);
		appendAsBytes<uint16_t>(array, propID);
	}

	array.append(value);
}

void padByteArray(QByteArray &array, int length, char padding)
{
	if(array.size() > length)
	{
		array.resize(length);
	}
	else if(array.size() < length)
	{
		array.append(length - array.size(), padding);
	}
}

QByteArray padString(const char *str, int length, char padding)
{
	QByteArray array(str);
	padByteArray(array, length, padding);
	return array;
}
