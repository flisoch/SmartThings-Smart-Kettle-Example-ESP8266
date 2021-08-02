# Create and update Custom Capability commands

1. Download smartthings-cli from https://github.com/SmartThingsCommunity/smartthings-cli/releases
2. Copy json config files of some default capability

    `$./smartthings capabilities thermostatHeatingSetpoint 1 -j -o capabilityCopy.json`
    
    `$./smartthings capabilities:presentation thermostatHeatingSetpoint 1 -j -o capabilityPresentationCopy.json`

3. Remove capability Id, version status fields, set new name and change other fields you want to customize
4. Create new custom capability and save new capability config file

    `$./smartthings capabilities:create -j -i capabilityCopy.json -o customCapability.json`
5. Set capability Id from newly created config to presentationCopy.json. Change other fields you want to customize
6. Create new custom capability presentation and its config file
    `$./smartthings capabilities:create -j -i capabilityPresentationCopy.json -o customCapabilityPresentation.json`

