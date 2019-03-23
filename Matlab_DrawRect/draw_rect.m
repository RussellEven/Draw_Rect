function [ dest ] = draw_rect( src, startPosition, rectSize,  lineSize, color )

[start_y, start_x] = deal(startPosition(1),startPosition(2));
[rect_size_w, rect_size_h] = deal(rectSize(1),rectSize(2));

[height, width, channel] = size(src);
if channel==1
    dest(:, : ,1) = src;
    dest(:, : ,2) = src;
    dest(:, : ,3) = src;
else
    dest = src;
end

for channel_i = 1 : 3              
    for line_i = 1 : lineSize		% expand inside
	gain = line_i-1;
         dest( start_y+gain, (start_x+gain):(start_x+rect_size_w-gain),       channel_i ) =  color(channel_i);	%above
         dest( start_y+rect_size_h-gain,  (start_x+gain):(start_x+rect_size_w-gain),       channel_i ) =  color(channel_i);	%bottom
         dest( (start_y+gain) : (start_y+rect_size_h-gain),     start_x+gain,              channel_i ) =  color(channel_i);	%left
         dest( (start_y+gain) : (start_y+rect_size_h-gain),     start_x+rect_size_w-gain,  channel_i ) =  color(channel_i);	%right
    end    
end 
