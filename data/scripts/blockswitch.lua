-- When a block is pushed onto the tile, activate

function modifyPulse(pulse, change)
	local p = getProperties(pulse)
	p['rate'] = p['rate'] * change
	p['current_rate'] = p['current_rate'] * change
end

function modifyAreaCounter(area, change, name)
	local p = getAreaProperties(area)

	if p[name] == nil then
		p[name] = 0
	end
	p[name] = p[name] + change
	print(name .. ": " .. areaprop[name])
end

if not isInitilized(self) then
	-- Apply a pulsating VFX
	local properties = {}
	local area = self.area
	local gx = self:getGridX()
	local gy = self:getGridY()
	local tile = area:getTile(gx, gy)
	properties['vfxscript'] = VfxScripted("vfx-pulsate.lua")
	tile:addVfx(properties['vfxscript'])

	setProperties(self, properties)
	areaprop = getAreaProperties(self.area)
	
	--areaprop['num_switches'] = 999
	modifyAreaCounter(self.area, 1, 'num_switches')
	modifyAreaCounter(self.area, 0, 'active_switches')
else
	-- Find the nearest Crate in the area
	local area = self.area
	local object = area:getNearestObjectByTag(self.location, "Crate")
	local properties = getProperties(self)

	-- If the nearest Crate is on the switch
	if object and object:getGridX() == self:getGridX() and object:getGridY() == self:getGridY() then

		-- If its not actived, active is
		if not properties['active'] then
			print(self.tag .. " ACTIVEATED " .. object:getGridX() .. "x" .. object:getGridY() .. " = " .. self:getGridX() .. "x" .. self:getGridY())

			-- Make the crate pulse
			properties['cratevfx'] = VfxScripted("vfx-pulsate.lua")
			object:addVfx(properties['cratevfx'])
			--modifyPulse(vfxscripted, 4)

			-- Increase the pulse rate of the tile
			modifyPulse(properties['vfxscript'], 4)

			-- Increate the tile active count for the area
			--[[if not isInitilized(area) then
				ap = {}
				ap['init'] = true
				setProperties(area, ap)
			end]]--

			--areaprop = getProperties(self.area)
			--modifyShared(self.area, 1)

			--print(self.area:getMemoryAddress())

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
		end
	end
end

--print(self:getMemoryAddress())
