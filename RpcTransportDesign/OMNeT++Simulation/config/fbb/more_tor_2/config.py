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
for i in range(36):
	print template_config.format(i * 16, i * 16 + 15, i)
for i in range(144 * 4):
	print template_host.format(i)
