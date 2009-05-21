-- Teleporter script
if not isInitilized(self) then
	local properties = {}

	-- Apply a pulsating blue VFX to the tile the teleporter is on
	local gx = self:getGridX()
	local gy = self:getGridY()
	local area = self.area
	local tile = area:getTile(gx, gy)
	properties['vfxscript'] = VfxScripted("vfx-pulsate-blue.lua")
	tile:addVfx(properties['vfxscript'])

	setProperties(self, properties)
else
	-- If the player is within teleport range
	local player = getPlayer()
	if player and self:getDistanceTo(player) < 1.0 then
		local p = getProperties(self)

		-- Find the destination object, to teleport player there		
		local destination = getObjectByTag(self.tag .. "_DST")
		if destination then
			player.location = destination
		else
			print("Could not find '" .. self.tag .. "_DST" .. "'")
		end
	end
end
