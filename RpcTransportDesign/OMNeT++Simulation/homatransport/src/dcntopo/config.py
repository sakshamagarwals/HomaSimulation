template_host = """    <hostConfig id={}>
        <transportConfig>
        </transportConfig>
        <appConfig>
            <isSender>true</isSender>
            <destIds>-1</destIds>
        </appConfig>
    </hostConfig>"""


for i in range(288):
	print template_host.format(i)
