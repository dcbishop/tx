-- Teleporter script
if not isInitilized(self) then
	local properties = {}

	-- Apply a pulsating VFX
	local gx = self:getGridX()
	local gy = self:getGridY()
	local area = self.area
	local tile = area:getTile(gx, gy)
	properties['vfxscript'] = VfxScripted("vfx-pulsate-blue.lua")
	tile:addVfx(properties['vfxscript'])

	setProperties(self, properties)
else
	if self:getDistanceTo(getPlayer()) < 1.0 then
		local p = getProperties(self)

		--[[if not p['areaLoaded'] then
			p['newArea'] = Area()
			p['newArea'].tag = "NewArea"
			gm:registerObject(p['newArea'])
			loadArea("data/areas/sokoban1.xml", p['newArea'])
			print("Load area")
			p['areaLoaded'] = true
		end]]--

		
		local destination = getObjectByTag(self.tag .. "_DST")
		print(destination.tag)
		if destination then
			getPlayer().location = destination
		end
	end
end
