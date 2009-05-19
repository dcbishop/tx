-- An automatic door that open when the player approaches.

if not isInitilized(self) then
	local properties = {}

	properties['vmodel'] = VModel("pointer.dae")

	local closeTag = self.tag .. "_CLOSE"
	local closeObj = Object(closeTag, properties['vmodel'])
	closeObj.isTempory = true
	closeObj.isVisible = false
	closeObj.location = self.location

	local openTag = self.tag .. "_OPEN"
	local openObj = Object(openTag, properties['vmodel'])
	openObj.isTempory = true
	openObj.isVisible = false
	openObj.location = self.location
	openObj.y = openObj.y + 1.5

	local area = self.area
	area:addObject(closeObj)
	area:addObject(openObj)

	properties['closeObj'] = closeObj
	properties['openObj'] = openObj
	properties['currentObj'] = closeObj

	-- If there is 'LOCKED' in the tag, set the state to locked
	properties['locked'] = false
	if string.find(self.tag, "LOCKED") then
		properties['locked'] = true
	end

	-- If the door is opened by switches then set the flag
	if string.find(self.tag, "SWITCHES") then
		properties['switches'] = true
	end

	setProperties(self, properties)
else
	local properties = getProperties(self)

	if properties['switches'] then
		pa = getAreaProperties(self.area)

		if pa['active_switches'] >= pa['num_switches'] then
			properties['locked'] = false
		else
			properties['locked'] = true
		end
	end

	--print(self.tag .. " Dis: " ..self:getDistanceTo(getPlayer()))
	if self:getDistanceTo(getPlayer()) < 1.5 then
		if properties['locked'] == false then
			properties['currentObj'] = properties['openObj']
		end
	else
		properties['currentObj'] = properties['closeObj']
	end

	local currentObj = properties['currentObj']
	local speed = 0.001
	local ds = speed * getTimeDiff()


	if self:getDistanceTo(currentObj) > speed then
		if self.y < currentObj.y then
			self.y = self.y + speed
		elseif self.y > currentObj.y then
			self.y = self.y - speed
		end
	end
end
