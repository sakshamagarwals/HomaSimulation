template_host = """    <hostConfig id=\"{}\">
        <transportConfig>
        </transportConfig>
        <appConfig>
            <isSender>true</isSender>
            <destIds>-1</destIds>
        </appConfig>
    </hostConfig>"""

template_config = """<interface hosts='**.host[{}..{}]' address='10.x.{}.x' netmask='255.x.x.x'/>
"""
template_head = """<topologyConfig>
    <param>
    </param>

    <IPv4Configurator> 
    {}
    </IPv4Configurator>
    {}
</topologyConfig>"""

config1 = ""
config2 = ""
for i in range(8):
	config1 += template_config.format(i * 64, i * 64 + 63, i) + "\n"
for i in range(64 * 8):
	config2 += template_host.format(i) + "\n"

print template_head.format(config1, config2)
