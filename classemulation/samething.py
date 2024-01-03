#!/usr/bin/python3
# coding: utf-8

"""
    classemulation 1.0 - For comparison, the same thing in Python.

    Copyright (C) 2024 Hauke Lubenow

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
"""

class Lamp:

    def __init__(self, name, lightintensity, state):
        self.name           = name
        self.lightintensity = lightintensity
        self.state          = state

    def switchOn(self):
        self.state = "on"
        print("'" + self.name + "' is on at " + str(self.lightintensity) + " Watt.")

    def switchOff(self):
        self.state = "off"
        print("'" + self.name + "' is off.")

    def newLightBulb(self, light):
        if self.state == "on":
            print("Light bulb can not be changed.")
            print("First, '" + self.name + "' has to be switched off.")
        else:
            self.lightintensity = light
            print("Light bulb in '" + self.name + "' has been changed.")
            print("The new bulb has " + str(self.lightintensity) + " Watt.")
            self.switchOn()

def main():
    lamp1 = Lamp("First Lamp", 50, "off")
    lamp2 = Lamp("Second Lamp", 40, "off")
    lamp1.switchOn()
    lamp2.switchOn()
    lamp2.newLightBulb(100)
    lamp2.switchOff()
    lamp2.newLightBulb(100)

main()
