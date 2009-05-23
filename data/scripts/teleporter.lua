-- Teleporter script
if not isInitilized(self) then
	local properties = {}


	local gx = self:getGridX()
	local gy = self:getGridY()
	local area = self.area

	local location = area:getLocationFromGridCoord(gx, gy)

	-- Spawn the teleporter panel
	properties['plate_vmodel'] = VModel("plate.dae")	
	local plateObj = Object(self.tag .. "_PLATE", properties['plate_vmodel'])
	plateObj.isTempory = true
	plateObj.location = location
	plateObj.y = plateObj.y + 0.01
	properties['plate_object'] = plateObj

	-- Spawn the metal frame around the teleporter
	properties['frame_vmodel'] = VModel("frame.dae")
	local frameObj = Object(self.tag .. "_FRAME", properties['frame_vmodel'])
	frameObj.isTempory = true
	frameObj.location = location
	frameObj.y = frameObj.y + 0.01
	properties['frame_object'] = frameObj

	-- Apply a pulsating blue VFX to the teleporter is on
	properties['vfxscript'] = VfxScripted("vfx-pulsate-blue.lua")
	plateObj:addVfx(properties['vfxscript'])

	self.isVisible = false


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
			--print("Could not find '" .. self.tag .. "_DST" .. "'")
		end
	end
end
