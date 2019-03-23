% function: draw rect in arbitrary position and achieve magnification
% effect in the lower right corner of image.

clc;
clear;
im_src = double(imread('image_Lena512rgb.png'));
[height, width, channel1] = size(im_src);

% define the start position, the rect size, the magnification factor
[start_y, start_x] = deal(230, 140);

rect_size = 30;
m_factor = 4;

% acquire magnificated rect
tt = im_src(start_y:start_y+rect_size-1, start_x:start_x+rect_size-1, :);
tt_big = imresize(tt,m_factor);
[m_height, m_width, channel2]=size(tt_big);

% achieve magnificated in the lower right corner of image
if channel1 == 3
    for i=1:3
        im_src(height-m_height+1:height, width-m_width+1:width, i)=tt_big(:,:,i);
    end
else
    im_src(height-m_height+1:height, width-m_width+1:width)=tt_big;
end

% draw two rects in the image 
s=draw_rect(im_src, [start_y,start_x],[rect_size, rect_size], 3, [255, 0, 0]);
result=draw_rect(s, [height-m_height, width-m_width],[m_height, m_width], 3, [255, 0, 0]);

imshow(uint8(result));
imwrite(uint8(result), 'test.png');