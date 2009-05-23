-- Destination Pad - Spawns destination graphics
if not isInitilized(self) then
	local properties = {}

	local gx = self:getGridX()
	local gy = self:getGridY()
	local area = self.area

	local location = area:getLocationFromGridCoord(gx, gy)

	-- Spawn the teleporter pad
	properties['plate_vmodel'] = VModel("plate.dae")	
	local plateObj = Object(self.tag .. "_PLATE", properties['plate_vmodel'])
	plateObj.isTempory = true
	plateObj.location = location
	plateObj.y = plateObj.y + 0.01
	properties['plate_object'] = plateObj

	-- Spawn the metal frame around the pad
	properties['frame_vmodel'] = VModel("frame.dae")
	local frameObj = Object(self.tag .. "_FRAME", properties['frame_vmodel'])
	frameObj.isTempory = true
	frameObj.location = location
	frameObj.y = frameObj.y + 0.01
	properties['frame_object'] = frameObj

	setProperties(self, properties)
end
