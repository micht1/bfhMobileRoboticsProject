function varargout = YellowGUI(varargin)
% YELLOWGUI MATLAB code for YellowGUI.fig
%      YELLOWGUI, by itself, creates a new YELLOWGUI or raises the existing
%      singleton*.
%
%      H = YELLOWGUI returns the handle to a new YELLOWGUI or the handle to
%      the existing singleton*.
%
%      YELLOWGUI('CALLBACK',hObject,eventData,handles,...) calls the local
%      function named CALLBACK in YELLOWGUI.M with the given input arguments.
%
%      YELLOWGUI('Property','Value',...) creates a new YELLOWGUI or raises the
%      existing singleton*.  Starting from the left, property value pairs are
%      applied to the GUI before YellowGUI_OpeningFcn gets called.  An
%      unrecognized property name or invalid value makes property application
%      stop.  All inputs are passed to YellowGUI_OpeningFcn via varargin.
%
%      *See GUI Options on GUIDE's Tools menu.  Choose "GUI allows only one
%      instance to run (singleton)".
%
% See also: GUIDE, GUIDATA, GUIHANDLES

% Edit the above text to modify the response to help YellowGUI

% Last Modified by GUIDE v2.5 25-Apr-2019 12:52:25

% Begin initialization code - DO NOT EDIT
gui_Singleton = 1;
gui_State = struct('gui_Name',       mfilename, ...
                   'gui_Singleton',  gui_Singleton, ...
                   'gui_OpeningFcn', @YellowGUI_OpeningFcn, ...
                   'gui_OutputFcn',  @YellowGUI_OutputFcn, ...
                   'gui_LayoutFcn',  [] , ...
                   'gui_Callback',   []);
if nargin && ischar(varargin{1})
    gui_State.gui_Callback = str2func(varargin{1});
end

if nargout
    [varargout{1:nargout}] = gui_mainfcn(gui_State, varargin{:});
else
    gui_mainfcn(gui_State, varargin{:});
end
% End initialization code - DO NOT EDIT


% --- Executes just before YellowGUI is made visible.
function YellowGUI_OpeningFcn(hObject, eventdata, handles, varargin)
% This function has no output args, see OutputFcn.
% hObject    handle to figure
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)
% varargin   command line arguments to YellowGUI (see VARARGIN)

% Choose default command line output for YellowGUI


% if(~exist('yellow'))
%     
%     % Add our classes to the Matlab Java path
%     
%     dpath = {'./YellowInterface.jar', './protobuf-java-3.4.0.jar'};
%     javaclasspath(dpath);
%     import ch.bfh.roboticsLab.yellow.*;
%         
%     % Connect to the robot
%     yellow = SerialClient.getInstance;
%     
% end


handles.output = hObject;
% load('yellow.mat')
im = imread('noMap.png');
axes(handles.axes2);
imshow(im)
axis off

axes(handles.axes4);
imshow(im)
axis off
set(handles.status,'String','Standby')

% Update handles structure
guidata(hObject, handles);

% UIWAIT makes YellowGUI wait for user response (see UIRESUME)
% uiwait(handles.figure1);


% --- Outputs from this function are returned to the command line.
function varargout = YellowGUI_OutputFcn(hObject, eventdata, handles) 
% varargout  cell array for returning output args (see VARARGOUT);
% hObject    handle to figure
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)

% Get default command line output from handles structure
varargout{1} = handles.output;



% --- Executes on button press in navigate.
function navigate_Callback(hObject, eventdata, handles)
% hObject    handle to navigate (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)
%navigates on button press from start point to target point
if(~exist('yellow'))
    
    % Add our classes to the Matlab Java path
    
    dpath = {'./YellowInterface.jar', './protobuf-java-3.4.0.jar'};
    javaclasspath(dpath);
    import ch.bfh.roboticsLab.yellow.*;
        
    % Connect to the robot
    yellow = SerialClient.getInstance;
    
end


x = str2num(get(handles.endX,'String'));
y = str2num(get(handles.endY,'String'));
a = str2num(get(handles.endA,'String'));
%print Map with end coordinate
sX = str2num(get(handles.startX,'String'));
sY = str2num(get(handles.startY,'String'));
sA = degtorad(str2num(get(handles.startA,'String')));

load('mapFile')

%yellow set new Position and Orienatation
yellowString = sprintf('correctedPose: { x: %f, y: %f, alpha: %f}',sY*0.1,sX*0.1,sA);
yellow.set(yellowString);
pause(2);

%generate enlarged walls map and fedd navigation algorythm with it

    bwDist = gMap;
    %bwDist(bwDist==200)=255;
    se = strel('square',3);
    bwDist1 = imerode(double(bwDist),se);
    bwDist1(gMap==200)=200;
    bwDist2 = bwDist1;
    bwDist2(bwDist1==200)=0;
 telemetry = yellow.receive;
    viaPoints=navToPoint(bwDist2,double([x y]).*0.1,0.1,[0 0].*0.1,[telemetry.odometry.pose.y telemetry.odometry.pose.x])
    
    viaCnt=1;
    matSize=size(viaPoints)
    
    oldPose = [0 0 0];
    %follow path
    while(viaCnt<=matSize(1))
        pause(0.5);
        telemetry = yellow.receive;
        oldPose = [telemetry.odometry.pose.x telemetry.odometry.pose.y telemetry.odometry.pose.alpha];
        driveToPosition(viaPoints(viaCnt,2),viaPoints(viaCnt,1),viaPoints(viaCnt,3),yellow);
        waitForResending = 3;
        atPos = false;
        
        %pause(10);
        while(atPos==false)
            
            [atPos,telemetry]=isAtPosition(viaPoints(viaCnt,2),viaPoints(viaCnt,1),viaPoints(viaCnt,3),0.05,yellow);
            pause(0.5);
            actualPose = [telemetry.odometry.pose.x telemetry.odometry.pose.y telemetry.odometry.pose.alpha]
            if(waitForResending<1 & (norm(actualPose(1:2)-oldPose(1:2)))<0.01)
                driveToPosition(viaPoints(viaCnt,2),viaPoints(viaCnt,1),viaPoints(viaCnt,3),yellow);
                waitForResending = 3;
            else
                waitForResending = waitForResending-1;
            end
        end
        viaCnt=viaCnt+1;
    end











% --- Executes on button press in localize.
function localize_Callback(hObject, eventdata, handles)
% hObject    handle to localize (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)
%call localize function

clear 'localisation'
[coordinate,orientation]= guiLocalization;
x = num2str(coordinate(1));
y = num2str(coordinate(2));
a = num2str(orientation);

load('mapFile')
tempMap = gMap;
tempMap(coordinate(2),coordinate(1))= 100;

set(handles.startX,'String',x)
set(handles.startY,'String',y)
set(handles.startA,'String',a)

tempMap = showMap(tempMap);
axes(handles.axes2);
imshow(tempMap)
axis off


function startX_Callback(hObject, eventdata, handles)
% hObject    handle to startX (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)

% Hints: get(hObject,'String') returns contents of startX as text
%        str2double(get(hObject,'String')) returns contents of startX as a double


% --- Executes during object creation, after setting all properties.
function startX_CreateFcn(hObject, eventdata, handles)
% hObject    handle to startX (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    empty - handles not created until after all CreateFcns called

% Hint: edit controls usually have a white background on Windows.
%       See ISPC and COMPUTER.
if ispc && isequal(get(hObject,'BackgroundColor'), get(0,'defaultUicontrolBackgroundColor'))
    set(hObject,'BackgroundColor','white');
end



function startY_Callback(hObject, eventdata, handles)
% hObject    handle to startY (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)

% Hints: get(hObject,'String') returns contents of startY as text
%        str2double(get(hObject,'String')) returns contents of startY as a double


% --- Executes during object creation, after setting all properties.
function startY_CreateFcn(hObject, eventdata, handles)
% hObject    handle to startY (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    empty - handles not created until after all CreateFcns called

% Hint: edit controls usually have a white background on Windows.
%       See ISPC and COMPUTER.
if ispc && isequal(get(hObject,'BackgroundColor'), get(0,'defaultUicontrolBackgroundColor'))
    set(hObject,'BackgroundColor','white');
end



function startA_Callback(hObject, eventdata, handles)
% hObject    handle to startA (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)

% Hints: get(hObject,'String') returns contents of startA as text
%        str2double(get(hObject,'String')) returns contents of startA as a double


% --- Executes during object creation, after setting all properties.
function startA_CreateFcn(hObject, eventdata, handles)
% hObject    handle to startA (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    empty - handles not created until after all CreateFcns called

% Hint: edit controls usually have a white background on Windows.
%       See ISPC and COMPUTER.
if ispc && isequal(get(hObject,'BackgroundColor'), get(0,'defaultUicontrolBackgroundColor'))
    set(hObject,'BackgroundColor','white');
end



function endX_Callback(hObject, eventdata, handles)
% hObject    handle to endX (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)

% Hints: get(hObject,'String') returns contents of endX as text
%        str2double(get(hObject,'String')) returns contents of endX as a double
load('mapFile')
X = str2num(get(handles.endX,'String'));
Y = str2num(get(handles.endY,'String'));

sX = str2num(get(handles.startX,'String'));
sY = str2num(get(handles.startY,'String')); 

tempMap = gMap;
tempMap(Y,X)= 220;
tempMap(sY,sX)= 140;
tempMap = showMap(tempMap);

axes(handles.axes2);
imshow(tempMap)
axis off


% --- Executes during object creation, after setting all properties.
function endX_CreateFcn(hObject, eventdata, handles)
% hObject    handle to endX (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    empty - handles not created until after all CreateFcns called

% Hint: edit controls usually have a white background on Windows.
%       See ISPC and COMPUTER.
if ispc && isequal(get(hObject,'BackgroundColor'), get(0,'defaultUicontrolBackgroundColor'))
    set(hObject,'BackgroundColor','white');
end



function endY_Callback(hObject, eventdata, handles)
% hObject    handle to endY (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)

% Hints: get(hObject,'String') returns contents of endY as text
%        str2double(get(hObject,'String')) returns contents of endY as a double
load('mapFile')
X = str2num(get(handles.endX,'String'));
Y = str2num(get(handles.endY,'String'));

sX = str2num(get(handles.startX,'String'));
sY = str2num(get(handles.startY,'String')); 

tempMap = gMap;
tempMap(Y,X)= 220;
tempMap(sY,sX)= 140;
tempMap = showMap(tempMap);

axes(handles.axes2);
imshow(tempMap)
axis off

% --- Executes during object creation, after setting all properties.
function endY_CreateFcn(hObject, eventdata, handles)
% hObject    handle to endY (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    empty - handles not created until after all CreateFcns called

% Hint: edit controls usually have a white background on Windows.
%       See ISPC and COMPUTER.
if ispc && isequal(get(hObject,'BackgroundColor'), get(0,'defaultUicontrolBackgroundColor'))
    set(hObject,'BackgroundColor','white');
end



function endA_Callback(hObject, eventdata, handles)
% hObject    handle to endA (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)

% Hints: get(hObject,'String') returns contents of endA as text
%        str2double(get(hObject,'String')) returns contents of endA as a double
load('mapFile')
X = str2num(get(handles.endX,'String'));
Y = str2num(get(handles.endY,'String'));

sX = str2num(get(handles.startX,'String'));
sY = str2num(get(handles.startY,'String')); 

tempMap = gMap;
tempMap(Y,X)= 220;
tempMap(sY,sX)= 140;
tempMap = showMap(tempMap);

axes(handles.axes2);
imshow(tempMap)
axis off


% --- Executes during object creation, after setting all properties.
function endA_CreateFcn(hObject, eventdata, handles)
% hObject    handle to endA (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    empty - handles not created until after all CreateFcns called

% Hint: edit controls usually have a white background on Windows.
%       See ISPC and COMPUTER.
if ispc && isequal(get(hObject,'BackgroundColor'), get(0,'defaultUicontrolBackgroundColor'))
    set(hObject,'BackgroundColor','white');
end


% --- Executes on slider movement.
function speed_Callback(hObject, eventdata, handles)
% hObject    handle to speed (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)

% Hints: get(hObject,'Value') returns position of slider
%        get(hObject,'Min') and get(hObject,'Max') to determine range of slider




% --- Executes during object creation, after setting all properties.
function speed_CreateFcn(hObject, eventdata, handles)
% hObject    handle to speed (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    empty - handles not created until after all CreateFcns called

% Hint: slider controls usually have a light gray background.
if isequal(get(hObject,'BackgroundColor'), get(0,'defaultUicontrolBackgroundColor'))
    set(hObject,'BackgroundColor',[.9 .9 .9]);
end



% --- Executes on button press in autoStart.
function autoStart_Callback(hObject, eventdata, handles)
% hObject    handle to autoStart (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)
if(~exist('yellow'))
    
    % Add our classes to the Matlab Java path
    dpath = {'./YellowInterface.jar', './protobuf-java-3.4.0.jar'};
    javaclasspath(dpath);
    import ch.bfh.roboticsLab.yellow.*;
        
    % Connect to the robot
    yellow = SerialClient.getInstance;
    
end

speed = num2str(round(get(handles.speed,'Value')*10)/10)
str1 = 'reactiveParameters { translationalVelocity: ';
message = [str1 speed];
yellow.set(message);
yellow.set('state { stateName: AUTO_REACTIVE }')


% --- Executes on button press in autoStop.
function autoStop_Callback(hObject, eventdata, handles)
% hObject    handle to autoStop (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)

if(~exist('yellow'))
    
    % Add our classes to the Matlab Java path
    dpath = {'./YellowInterface.jar', './protobuf-java-3.4.0.jar'};
    javaclasspath(dpath);
    import ch.bfh.roboticsLab.yellow.*;
        
    % Connect to the robot
    yellow = SerialClient.getInstance;
    
end
yellow.set('state { stateName: OFF }')

% --- Executes on button press in mapStart.
function mapStart_Callback(hObject, eventdata, handles)
% hObject    handle to mapStart (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)
set(handles.status,'String','In Progress')
%call mapping function

%Connection to Yellow allready done in the different functions

lMap = getMap;
axes(handles.axes4);
imshow(lMap)
axis off

clear mapping
[gMap,mapZeroPoint] = mapping;

% loadedMap = imcomplement(imread("occupancyGrid_1.bmp"));
[tempMap,frontX,frontY] = showMap(gMap);

save('frontFile','frontX','frontY')

axes(handles.axes2);
imshow(tempMap)
axis off

set(handles.status,'String','Done')
% save('mapFile','gMap','loadedMap','mapZeroPoint')
save('mapFile','gMap','mapZeroPoint')


% --- Executes on button press in mapReset.
function mapReset_Callback(hObject, eventdata, handles)
% hObject    handle to mapReset (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)
set(handles.status,'String','Standby')
clear mapping
clear globalMap

im = imread('noMap.png');
axes(handles.axes2);
imshow(im)
axis off

axes(handles.axes4);
imshow(im)
axis off

