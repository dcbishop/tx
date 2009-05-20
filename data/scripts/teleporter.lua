-- Teleporter script
if not isInitilized(self) then
	-- Apply a pulsating VFX
	local properties = {}
	local area = self.area
	local gx = self:getGridX()
	local gy = self:getGridY()
	local tile = area:getTile(gx, gy)
	properties['vfxscript'] = VfxScripted("vfx-pulsate-blue.lua")
	tile:addVfx(properties['vfxscript'])

	areaprop = getAreaProperties(self.area)
	
	setProperties(self, properties)
else
	if self:getDistanceTo(getPlayer()) < 1.0 then
		p = getProperties(self)

		if not p['areaLoaded'] then
			p['newArea'] = Area()
			p['newArea'].tag = "NewArea"
			gm:registerObject(p['newArea'])
			loadArea("data/areas/sokoban1.xml", p['newArea'])
			print("Load area")
			p['areaLoaded'] = true
		end

		playerStart = p['newArea']:getObjectByTag("PlayerSpawn")
		getPlayer().location = playerStart
	end
end
