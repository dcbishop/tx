-- An automatic door that open when the player approaches

if not globals[addr] then
	properties = {}

	doorLocation = self.location

	vmodel = VModel("pointer.dae")

	closeTag = self.tag .. "_CLOSE"
	closeObj = Object(closeTag, vmodel)
	closeObj.isTempory = true
	closeObj.location = doorLocation

	openTag = self.tag .. "_OPEN"
	openObj = Object(openTag, vmodel)
	openObj.isTempory = true
	openObj.location = doorLocation
	openObj.y = openObj.y + 1.5

	area = self.area
	area:addObject(closeObj)
	area:addObject(openObj)

	properties['closeObj'] = closeObj
	properties['openObj'] = openObj

	properties['currentObj'] = closeObj

	globals[addr] = properties
end

properties = globals[addr]

if self:getDistanceTo(getPlayer()) < 1.5 then
	properties['currentObj'] = properties['openObj']
else
	properties['currentObj'] = properties['closeObj']
end

currentObj = properties['currentObj']
speed = 0.001
ds = speed * getTimeDiff()


if self:getDistanceTo(currentObj) > speed then
	if self.y < currentObj.y then
		self.y = self.y + speed
	elseif self.y > currentObj.y then
		self.y = self.y - speed
	end
end
