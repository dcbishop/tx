-- When a block is pushed onto the tile, activate

function modifyPulse(pulse, change)
	local p = getProperties(pulse)
	if p then
		p['rate'] = p['rate'] * change
		p['current_rate'] = p['current_rate'] * change
	end
end

function modifyAreaCounter(area, change, name)
	local p = getAreaProperties(area)

	if p[name] == nil then
		p[name] = 0
	end
	p[name] = p[name] + change
end

if not isInitilized(self) then
	-- Apply a pulsating VFX
	local properties = {}
	local area = self.area
	local gx = self:getGridX()
	local gy = self:getGridY()
	--local tile = area:getTile(gx, gy)

	local location = area:getLocationFromGridCoord(gx, gy)
	
	--areaprop['num_switches'] = 999
	modifyAreaCounter(self.area, 1, 'num_switches')
	modifyAreaCounter(self.area, 0, 'active_switches')

	properties['plate_vmodel'] = VModel("plate.dae")	
	local plateObj = Object(self.tag .. "_PLATE", properties['plate_vmodel'])
	plateObj.isTempory = true
	plateObj.location = location
	plateObj.y = plateObj.y + 0.01
	properties['plate_object'] = plateObj

	properties['frame_vmodel'] = VModel("frame.dae")
	local frameObj = Object(self.tag .. "_FRAME", properties['frame_vmodel'])
	frameObj.isTempory = true
	frameObj.location = location
	frameObj.y = frameObj.y + 0.02
	properties['frame_object'] = frameObj

	properties['vfxscript'] = VfxScripted("vfx-pulsate.lua")
	plateObj:addVfx(properties['vfxscript'])
	areaprop = getAreaProperties(self.area)


	setProperties(self, properties)
else
	-- Find the nearest Crate in the area
	local area = self.area
	local object = area:getNearestObjectByTag(self.location, "Crate")
	local properties = getProperties(self)

	-- If the nearest Crate is on the switch
	if object and object:getGridX() == self:getGridX() and object:getGridY() == self:getGridY() then
		-- Speed up crate pulse effect
		if properties['active'] and properties['cratevfx'] and not properties['pulsefix'] then
			modifyPulse(properties['cratevfx'], 4)
			properties['pulsefix'] = true
		end

		-- If its not actived, active is
		if not properties['active'] then
			-- Make the crate pulse
			properties['cratevfx'] = VfxScripted("vfx-pulsate.lua")
			object:addVfx(properties['cratevfx'])

			-- Increase the pulse rate of the tile
			modifyPulse(properties['vfxscript'], 4)

			-- Set activation state
			properties['active'] = object
			modifyAreaCounter(self.area, 1, 'active_switches')
		end
	else
		-- If crate was moved off and we lost activation...
		if properties['active'] then
			print(self.tag .. " Lost activation")
			modifyAreaCounter(self.area, -1, 'active_switches')

			-- Decrease the pulse rate of the tile
			modifyPulse(properties['vfxscript'], 1/4)
			
			-- Remove VFX from crate
			local object = properties['active']
			object:removeVfx(properties['cratevfx'])
			--setProperties(properties['cratevfx'], nil)

			properties['cratevfx'] = nil
			properties['active'] = nil
			properties['pulsefix'] = false
		end
	end
end

--print(self:getMemoryAddress())
