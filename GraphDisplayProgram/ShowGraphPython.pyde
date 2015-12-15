h = int(600/1)
w = int(1200/2)
padding = 50
axispad = 60
xi = 0
yi = 0
zi = 0
mode = ''
colors = 1
colorNodes = []
bipartite = False
radius = 0.0
s = "C:/Users/Alex/Desktop/nodes.txt"


def setup():
    background(255) 
    size(w + padding, h + padding)
    graph(s)

def createSquareGraph():
    global radius
    frame.setTitle("Unit square RGG")
    fill(0)
    textAlign(CENTER, TOP)  # LEFT, RIGHT, CENTER
    
    #rect(x,y,width,height)
    noStroke()
    fill(255)
    rect(0, 0, width, padding)
    rect(0, 0, axispad, height)
    rect(width-padding, 0, padding, height)
    rect(0, height-axispad, width, axispad)
    fill(0)
    stroke(0)
    
    # Left
    line(axispad, padding, axispad, h - axispad + padding)
    # Top
    line(axispad, padding, w, padding)
    # Right
    line(w, padding, w, h - axispad + padding)
    # Bottom
    line(axispad, h - axispad + padding, w, h - axispad + padding)

    # X-axis
    # Lineas en X van desde axispad (50) hasta W
    divisions = 10
    dis = ((1.0) * (w - axispad) / divisions)
    subdis = dis/4.0
    for i in range(0, divisions + 1):
        line(axispad + (dis * i), h - axispad + padding, axispad + (dis * i), h - axispad + padding + 15)
        text(str((1.0 / divisions) * i), axispad + (dis * i), h - axispad + padding + 15)
        if i is not 0:
            for j in range(1,4):
                displacement = (dis * (i-1))
                line(axispad + (subdis * j)+displacement, h - axispad + padding, axispad + (subdis * j)+displacement, h - axispad + padding + 7)

    # Y-axis
    # Lineas en Y van desde padding hasta (h-axispad+padding)
    textAlign(RIGHT, CENTER)  # LEFT, RIGHT, CENTER
    divisions = 10
    dis = ((1.0) * (((h - axispad + padding)) - padding) / divisions)
    subdis = dis/4.0
    for i in range(0, divisions + 1):
        line(axispad, padding + (dis) * i, axispad - 15, padding + (dis) * i)
        text(str(1.0 - ((1.0 / divisions) * i)), axispad - 20, padding + (dis * i))
        if i is not 0:
            for j in range(1,4):
                displacement = (dis * (i-1))
                line(axispad, (padding + (subdis) * j)+displacement, axispad - 7, (padding + (subdis) * j)+displacement)
    
    #Write axis
    tx = width/2
    ty = 10
    textAlign(CENTER, CENTER)
    translate(tx,ty)
    rotate(-HALF_PI)
    text("Y-Coordinate",-height/2,-width/2+5)
    rotate(HALF_PI)
    translate(-tx,-ty)
    text("X-Coordinate",width/2,height-15)
    
    f = open("C:/Users/Alex/Desktop/graphData.txt")
    for lin in f:
        data = lin.split(" ")
        loc = 25
        divi=4
        print data[0]
        if data[0] == "avgdeg":
            text("Avg. Degree = "+data[1], width/divi*2, loc)
        elif data[0] == "maxdeg":
            text("Max Degree = "+data[1], width/divi*1, loc+20)
        elif data[0] == "colors":
            text("Colors = "+data[1], width/divi*2, loc+20)
        elif data[0] == "radius":
            radius = data[1]
            text("R = "+radius, width/divi*1, loc)
        elif data[0] == "vertices":
            text("N = "+data[1], width/divi*3, loc)
        elif data[0] == "terminalCliqueSize":
            text("Size of term. clique="+data[1], width/divi*3, loc+20)

def createCircleGraph():
    global radius
    frame.setTitle("Unit circle")
    stroke(0)
    fill(255,0)
    textAlign(CENTER, TOP)  # LEFT, RIGHT, CENTER
    
    #ellipse(X, Y, width, height)
    
    eraseBorder = padding
    strokeWeight(eraseBorder)
    stroke(255)
    ellipse(((w-axispad)/2)+axispad, ((h-axispad)/2)+padding, w-axispad+eraseBorder, h-axispad+eraseBorder)
    strokeWeight(1)
    stroke(0)
    fill(255,0)
    ellipse(((w-axispad)/2)+axispad, ((h-axispad)/2)+padding, w-axispad, h-axispad)
    
    # Left
    line(axispad, padding, axispad, h - axispad + padding)
    # Bottom
    line(axispad, h - axispad + padding, w, h - axispad + padding)
    
    
    # X-axis
    # Lineas en X van desde axispad (50) hasta W
    fill(0)
    divisions = 10
    dis = ((1.0) * (w - axispad) / divisions)
    subdis = dis/4.0
    for i in range(0, divisions + 1):
        line(axispad + (dis * i), h - axispad + padding, axispad + (dis * i), h - axispad + padding + 15)
        text(str((((2.0 / divisions) * i))-1), axispad + (dis * i), h - axispad + padding + 15)
        if i is not 0:
            for j in range(1,4):
                displacement = (dis * (i-1))
                line(axispad + (subdis * j)+displacement, h - axispad + padding, axispad + (subdis * j)+displacement, h - axispad + padding + 7)

    # Y-axis
    # Lineas en Y van desde padding hasta (h-axispad+padding)
    textAlign(RIGHT, CENTER)  # LEFT, RIGHT, CENTER
    dis = ((1.0) * (((h - axispad + padding)) - padding) / divisions)
    subdis = dis/4.0
    for i in range(0, divisions + 1):
        line(axispad, padding + (dis) * i, axispad - 15, padding + (dis) * i)
        text(str(2-(((2.0 / divisions) * i))-1), axispad - 20, padding + (dis * i))
        if i is not 0:
            for j in range(1,4):
                displacement = (dis * (i-1))
                line(axispad, (padding + (subdis) * j)+displacement, axispad - 7, (padding + (subdis) * j)+displacement)
    
    #Write axis
    tx = width/2
    ty = 10
    textAlign(CENTER, CENTER)
    translate(tx,ty)
    rotate(-HALF_PI)
    text("Y-Coordinate",-height/2,-width/2+5)
    rotate(HALF_PI)
    translate(-tx,-ty)
    text("X-Coordinate",width/2,height-15)
    f = open("C:/Users/Alex/Desktop/graphData.txt")
    for lin in f:
        data = lin.split(" ")
        loc = 25
        print data[0]
        if data[0] == "avgdeg":
            text("Avg. Degree = "+data[1], width/3*2, loc)
        elif data[0] == "maxdeg":
            text("Max Degree = "+data[1], width/3*1, loc+20)
        elif data[0] == "colors":
            text("Colors = "+data[1], width/3*2, loc+20)
        elif data[0] == "radius":
            radius = data[1]
            text("R = "+data[1], width/3*1, loc)
    
def createSphereGraph():
    global radius
    frame.setTitle("Unit sphere")
    textAlign(CENTER, TOP)  # LEFT, RIGHT, CENTER
    
    #ellipse(X, Y, width, height)
    stroke(0)
    ellipseMode(CORNER)
    fill(255,0)
    
    #Clean-up ellipses
    eraseBorder = axispad
    strokeWeight(eraseBorder)
    stroke(255)
    ellipse(axispad-eraseBorder/2, padding-eraseBorder/2, (w/2)-axispad+eraseBorder, h-axispad+eraseBorder)
    ellipse(w/2 + axispad-eraseBorder/2, padding-eraseBorder/2, (w/2)-axispad+eraseBorder, h-axispad+eraseBorder)
    strokeWeight(1)
    stroke(0)

    #Real elipses
    ellipse(axispad, padding, (w/2)-axispad, h-axispad)
    ellipse(w/2 + axispad, padding, (w/2)-axispad, h-axispad)
    
    # Left
    line(axispad, padding, axispad, h - axispad + padding)
    # Bottom
    line(axispad, h - axispad + padding, w/2, h - axispad + padding)
    # Left
    line(w/2 + axispad, padding, w/2 + axispad, h - axispad + padding)
    # Bottom
    line(w/2 + axispad, h - axispad + padding, w, h - axispad + padding)
    
    
    #For the first graph
    # X-axis
    # Lineas en X van desde axispad (50) hasta W
    fill(0)
    divisions = 5
    dis = ((1.0) * (w/2 - axispad) / divisions)
    for i in range(0, divisions + 1):
        line(axispad + (dis * i), h - axispad + padding, axispad + (dis * i), h - axispad + padding + 15)
        text(str((((2.0 / divisions) * i))-1), axispad + (dis * i), h - axispad + padding + 15)
    
    #For 2nd graph
    # X-axis
    # Lineas en X van desde axispad (50) hasta W
    fill(0)
    dis = ((1.0) * (w/2 - axispad) / divisions)
    for i in range(0, divisions + 1):
        line((w/2+axispad) + (dis * i), h - axispad + padding, (w/2+axispad) + (dis * i), h - axispad + padding + 15)
        text(str((((2.0 / divisions) * i))-1), (w/2+axispad) + (dis * i), h - axispad + padding + 15)

    
    # Y-axis
    # Lineas en Y van desde padding hasta (h-axispad+padding)
    textAlign(RIGHT, CENTER)  # LEFT, RIGHT, CENTER
    dis = ((1.0) * (((h - axispad + padding)) - padding) / divisions)
    for i in range(0, divisions + 1):
        line(axispad, padding + (dis) * i, axispad - 15, padding + (dis) * i)
        text(str(2-(((2.0 / divisions) * i))-1), axispad - 20, padding + (dis * i))
    
    
    # Y-axis
    # Lineas en Y van desde padding hasta (h-axispad+padding)
    textAlign(RIGHT, CENTER)  # LEFT, RIGHT, CENTER
    dis = ((1.0) * (((h - axispad + padding)) - padding) / divisions)
    for i in range(0, divisions + 1):
        line(w/2+axispad, padding + (dis) * i, (w/2+axispad) - 15, padding + (dis) * i)
        text(str(2-(((2.0 / divisions) * i))-1), (w/2+axispad) - 20, padding + (dis * i))
        
    textAlign(CENTER, CENTER)
    textFont(font, 15*1.5)
    textSize(20)
    text("Top half of the sphere (Z >= 0)",((w+axispad+padding)/4)*1,padding/2)
    text("Bottom half of the sphere (Z < 0)",((w+padding)/4)*3,padding/2)
    
    #Write axis
    tx = width/2
    ty = 10
    textSize(16)
    textAlign(CENTER, CENTER)
    translate(tx,ty)
    rotate(-HALF_PI)
    text("Y-Coordinate",-height/2,-width/2+5)
    rotate(HALF_PI)
    translate(-tx,-ty)
    text("X-Coordinate",width/2,height-15)
    
    f = open("C:/Users/Alex/Desktop/graphData.txt")
    for lin in f:
        data = lin.split(" ")
        loc = 25
        print data[0]
        i = 4
        divs = 9
        if data[0] == "avgdeg":
            text("Avg. Degree = "+data[1], width/divs*(i+1), loc)
        elif data[0] == "maxdeg":
            text("Max Degree = "+data[1], width/divs*i, loc+20)
        elif data[0] == "colors":
            text("Colors = "+data[1], width/divs*(i+1), loc+20)
        elif data[0] == "radius":
            radius = data[1]
            text("R = "+data[1], width/divs*i, loc)
    
def graph(s):
    global font, colorNodes, bipartite, radius
    stroke(0)
    strokeWeight(1)
    # Font, 16 point, anti-aliasing
    font = createFont("Helvetica", 16, True)
    # Font variable and size
    textFont(font, 15)
    f = open(s)
    for lin in f:
        data = lin.split(" ")
        # print data
        x = float(data[1])
        y = float(data[2])
        z = float(data[3])
        ncolor = int(data[4])

        if data[0] == 'c':  # Setup for circle mode
            #createCircleGraph()
            mode = 'c'
            
        elif data[0] == 'u':  # Setup for unit square mode
            #createSquareGraph()
            mode = 'u'

        elif data[0] == 's':  # Setup for sphere mode
            #createSphereGraph()
            wcanvas = (w/2)-axispad
            hcanvas = (height-axispad) - padding
            mode = 's';

        elif data[0] == 'k':  # Say how many distinct colors
            colors = int(data[1])
            print "Colors needed", colors

        # Have to draw a node
        elif data[0] == 'n':
            noStroke();
            if mode == 'u':  # Unit square
                xi = x * (w - axispad) + axispad
                yi = y * (h - axispad) + padding
                colorNodes.append((xi, yi, ncolor, 0, bipartite))

            elif mode == 'c':  # Circle
                xi = (x/2 * (w - axispad) + axispad)
                yi = (y/2 * (h - axispad) + padding)
                colorNodes.append((xi, yi, ncolor, 0, bipartite))
                
            elif mode == 's':  # Sphere
                xi = floor( ((x+1.0)/2.0) * (wcanvas) ) + axispad
                yi = floor( ((y+1.0)/2.0) * (hcanvas) ) + padding
                zi = z
                
                if zi >= 0:
                    colorNodes.append((xi, yi, ncolor, 0, bipartite))
                else:
                    colorNodes.append((xi + w/2, yi, ncolor, 0, bipartite))

        # Have to draw an edge
        elif data[0] == 'e':  # Need to draw an edge 
            stroke(0)
            if mode == 'u':  # Unit square
                line(xi, yi, x * (w - axispad) + axispad, y * (h - axispad) + padding)

            elif mode == 'c':  # Circle
                line(xi, yi, (x/2 * (w - axispad) + axispad), (y/2 * (h - axispad) + padding))

            elif mode == 's':  # Sphere
                xl = floor( ((x+1.0)/2.0) * (wcanvas) ) + axispad
                yl = floor( ((y+1.0)/2.0) * (hcanvas) ) + padding
                if z >= 0:
                    if zi < 0:
                        stroke(205);
                        
                    else:
                        stroke(0)
                    line(xi,yi,xl,yl)
                else:
                    if zi >= 0:
                        stroke(205);
                    else:
                        stroke(0)
                    offset = w/2
                    line(xi+offset,yi,xl+offset,yl)
                
        # Have to draw a terminal clique node
        elif data[0] == 'l':
            noStroke()
            if mode == 'u':  # Unit square
                xi = x * (w - axispad) + axispad;
                yi = y * (h - axispad) + padding;
                colorNodes.append((xi, yi, 0, 1, bipartite))

            elif mode == 'c':  # Unit square
                xi = (x/2 * (w - axispad) + axispad)
                yi = (y/2 * (h - axispad) + padding)
                colorNodes.append((xi, yi, 0, 1, bipartite))

            elif mode == 's':
                xi = floor( ((x+1.0)/2.0) * (wcanvas) ) + axispad
                yi = floor( ((y+1.0)/2.0) * (hcanvas) ) + padding
                zi = z
                if zi >= 0:
                    colorNodes.append((xi, yi, ncolor, 1, bipartite))
                else:
                    colorNodes.append((xi + w/2, yi, ncolor, 1, bipartite))
                    
        elif data[0] == 'max':
            if mode == 'u':  # Unit square
                xi = x * (w - axispad) + axispad;
                yi = y * (h - axispad) + padding;
                colorNodes.append((xi, yi, 0, 0, True,'max'))
                
            elif mode == 'c':  # Unit circle
                xi = (x/2 * (w - axispad) + axispad)
                yi = (y/2 * (h - axispad) + padding)
                colorNodes.append((xi, yi, 0, 0, True,'max'))
                
            elif mode == 's':
                xi = floor( ((x+1.0)/2.0) * (wcanvas) ) + axispad
                yi = floor( ((y+1.0)/2.0) * (hcanvas) ) + padding
                zi = z
                if zi >= 0:
                    colorNodes.append((xi, yi, ncolor, 0, False,'max'))
                else:
                    colorNodes.append((xi + w/2, yi, ncolor, 0, False,'max'))
                    
        elif data[0] == 'min':
            if mode == 'u':  # Unit square
                xi = x * (w - axispad) + axispad;
                yi = y * (h - axispad) + padding;
                colorNodes.append((xi, yi, 0, 0, False,'min'))
                
            elif mode == 'c':  # Unit circle
                xi = (x/2 * (w - axispad) + axispad)
                yi = (y/2 * (h - axispad) + padding)
                colorNodes.append((xi, yi, 0, 0, False,'min'))
                
            elif mode == 's':
                xi = floor( ((x+1.0)/2.0) * (wcanvas) ) + axispad
                yi = floor( ((y+1.0)/2.0) * (hcanvas) ) + padding
                zi = z
                if zi >= 0:
                    colorNodes.append((xi, yi, ncolor, 0, False, 'min'))
                else:
                    colorNodes.append((xi + w/2, yi, ncolor, 0, False,'min'))
                    
    for node in colorNodes:
        ellipseMode(CENTER)
        colorMode(HSB, 255)
        noStroke()
        if (node[3] == 1):
            stroke(123)
            fill(color(0, 0, 0))
            ellipse(node[0], node[1], 7, 7)
        else:
            if (node[4] == True): #If Bipartite = true
                colorMode(HSB, 255)
                fill(200,255,200,20)
                if mode == 's':
                    print "RADIUS IS =",radius
                    ellipse(node[0], node[1], float(radius)*(width/2-axispad-padding), float(radius)*(height-padding-axispad))
                elif mode =='c':
                    ellipse(node[0], node[1], float(radius)*(width-axispad-padding), float(radius)*(height-padding-axispad))
                else:
                    print "RADIUS IS =",radius
                    ellipse(node[0], node[1], (2.0*float(radius))*(width-(axispad+padding)), (2.0*float(radius))*(height-padding-axispad))
            noStroke()
            if(len(node) > 5):
                print "Dibuja Max/Min"
                colorMode(HSB, 255)
                colorMode(RGB)
                #Color min-max respectively
                if node[5] == 'max':
                    stroke(255,0,0)
                    fill(255,0,0,70)
                else: #min
                    stroke(0,0,255)
                    fill(0,0,255,70)
                    
                if mode == 's':
                    ellipse(node[0], node[1], float(radius)*(width/2-axispad-padding), float(radius)*(height-padding-axispad))
                elif mode == 'c':
                    ellipse(node[0], node[1], float(radius)*(width-axispad-padding), float(radius)*(height-padding-axispad))
                else:
                    ellipse(node[0], node[1], 2.0*float(radius)*(width-axispad-padding), 2.0*float(radius)*(height-padding-axispad))
                colorMode(HSB, 255)
            fill(color(node[2]*(255/colors) % 255, 255, 255))
            ellipse(node[0], node[1], 7, 7)
            noStroke()
    if mode == 'c':  # Setup for circle mode
        createCircleGraph()
    elif mode == 'u':  # Setup for unit square mode
        stroke(0)
        createSquareGraph()
    elif mode == 's':  # Setup for sphere mode
        createSphereGraph()
    colorNodes = []
        
def keyPressed():
    global bipartite
    print "PASO POR AQUI"
    xi = 0
    yi = 0
    zi = 0
    colors = 1
    colorNodes = []
    if key == '1':
        background(255) 
        s = "C:/Users/Alex/Desktop/bipartite1.txt"
        bipartite = True
        graph(s)
    if key == '2':
        background(255) 
        s = "C:/Users/Alex/Desktop/bipartite1.txt"
        bipartite = False
        graph(s)
    if key == '3':
        background(255) 
        s = "C:/Users/Alex/Desktop/bipartite2.txt"
        bipartite = True
        graph(s)
    if key == '4':
        background(255) 
        s = "C:/Users/Alex/Desktop/bipartite2.txt"
        bipartite = False
        graph(s)
    elif key == 'g':
        background(255) 
        s = "C:/Users/Alex/Desktop/nodes.txt"
        bipartite = False
        graph(s)

def draw():
    asdf=1
#   if (keyPressed):
#     if (key == 'b' || key == 'B'):
#       fill(0)
#   else
#     fill(255)
#   rect(25, 25, 50, 50)