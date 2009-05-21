-- Pulsates yellow

if not isInitilized(self) then
	local properties = {}

	properties['vfx'] = VfxColour(0.5, 0.5, 1.0, 1.0)
	self:setVfx(properties['vfx'])
	properties['rate'] = 1.0
	properties['current_rate'] = properties['rate']
	properties['min'] = 0.2
	properties['max'] = 1.0
	properties['pulse'] = properties['min']
	setProperties(self, properties)
else
	local properties = getProperties(self)

	if properties['pulse'] > properties['max'] then
		properties['current_rate'] = -properties['rate']
	end

	if properties['pulse'] < properties['min'] then
		properties['current_rate'] = properties['rate']
	end
	
	dt = (time - self.last_update) / 1000
	properties['pulse'] = properties['pulse'] + properties['current_rate'] * dt
	properties['vfx']:setColour(properties['pulse']*0.3, properties['pulse']*0.3, properties['pulse'], 1.0)
end
