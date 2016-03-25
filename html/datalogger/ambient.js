$(function() {
 
    var x_values = [];
    var y_values = [];
    var switch1 = true;
    $.get('data.php', {identifier: "ambient", time: set_time }, function(data) {
 
        data = data.split('/');
        for (var i in data)
        {
            if (switch1 == true)
            {
                x_values.push(data[i]);
                switch1 = false;
            }
            else
            {
                y_values.push(parseFloat(data[i]));
                switch1 = true;
            }
 
        }
        x_values.pop();
 
        $('#ambient').highcharts({
            chart : {
                type : 'spline'
            },
            title : {
                text : 'Ambient'
            },
            subtitle : {
                text : 'last 24h'
            },
            xAxis : {
                tickInterval:30,
                title : {
                    text : 'Time'
                },
                categories : x_values
            },
            yAxis : {
                min: 0,
                max: 255,
                tickInterval:50,
                title : {
                    text : 'Ambient'
                },
                labels : {
                    formatter : function() {
                        return this.value + "%"
                    }
                }
            },
            tooltip : {
                crosshairs : true,
                shared : true,
                valueSuffix : ''
            },
            plotOptions : {
                spline : {
                    marker : {
                        radius : 4,
                        lineColor : '#666666',
                        lineWidth : 1
                    }
                }
            },
            exporting: { enabled: false },
            series : [{
                showInLegend: false,
                name : 'Ambient',
                data : y_values
            }]
        });
    });
});
