//
// Retro PMD-85 console printable 3D case.
//

include <fc.scad>;
include <rpi1Aplus.scad>;

drawCaseBottom=0;
drawCaseTop=0;
drawPi=0;
drawAll=1;

$fn=50;

//------------------------------

//CASE BOTTOM

bottomThick=2;
bottomX=56;
bottomY=65;
bottomMountHeight=2.26;
bottomMountDia=5.5;
bottomHeight=bottomThick+bottomMountHeight+piThick+microHeight/2;

module case_bottom() {
    difference() {
        translate([0,0,0]) rounded_rect(bottomX, bottomY, bottomHeight, bottomThick);// BASE
        translate([0,0,bottomThick]) cube([bottomX, bottomY, bottomHeight]); // FILLER
        translate([0,0,bottomThick+bottomMountHeight]) rpi(edgeCut=3);// RPI
        bottom_hole();// BOTTOM HOLE
        for (vspace=[1:5])// VENT
            translate([piX/4-2, 10*vspace+2.5, -1]) rounded_rect(bottomX/2+4, 1, bottomThick+2, 1);
        translate([cardX, -bottomThick, bottomThick+bottomMountHeight]) sd_lip();// SD LIP
        translate([usbX-1,bottomY+bottomThick/2,bottomThick+bottomMountHeight+piThick-1]) usb_lip();// USB LIP
        translate([bottomX+bottomThick/2,microY-1,bottomThick+bottomMountHeight+piThick-1])// MICRO LIP
            micro_lip();
        translate([0,0,bottomHeight-1]) lip_lock_bottom();// LIPLOCK
    }
    bottom_mount(piHoleOffset, piHoleOffset, bottomThick);// BOTTOM MOUNT
    bottom_mount(piX-piHoleOffset,piHoleOffset, bottomThick);
    bottom_mount(piHoleOffset, piY-piHoleOffset, bottomThick);
    bottom_mount(piX-piHoleOffset, piY-piHoleOffset, bottomThick);
}

//CASE TOP

topThick=2;
topX=56;
topY=65;
topMountHeight=2.26;
topMountDia=5.5;
topHeight=10;

module case_top() {
    difference() {
        translate([0,0,0]) rounded_rect(topX, topY, topHeight+1, topThick);// BASE
        translate([0,0,-topThick]) cube([topX, topY, topHeight]);// FILLER
        translate([0,0,-microHeight/2-piThick]) rpi(edgeCut=3);// RPI
        translate([usbX-1, topY+bottomThick/2+0.5, -microHeight/2-0.5]) usb_lip();// USB LIP
        translate([bottomX+bottomThick/2+0.5, microY-1-0.5, -microHeight/2-0.5]) micro_lip();// MICRO LIP
        translate([-0.5,-0.5,-1]) lip_lock_top();//LIP LOCK
    }
    //TOP MOUNT
    top_mount(piHoleOffset, piHoleOffset, topThick);// BOTTOM MOUNT
    top_mount(piX-piHoleOffset,piHoleOffset, topThick);
    top_mount(piHoleOffset, piY-piHoleOffset, topThick);
    top_mount(piX-piHoleOffset, piY-piHoleOffset, topThick);
}

//------------------------------

if (drawCaseTop) {
//    translate([topX+topThick+0.5, topThick+0.5, topHeight])
//        rotate([0,180,0]) case_top();
    translate([topThick+0.5, topThick+0.5, 0]) case_top();
}

if (drawPi) {
    translate([0,0,bottomThick+bottomMountHeight]) rpi();
}

if (drawCaseBottom) {
    translate([0, 0, 0]) case_bottom();
}

if (drawAll) {
    translate([0,0,0]) case_bottom();
    translate([0,0,bottomThick+bottomMountHeight+10]) rpi();
    translate([0,0,bottomHeight+20]) case_top();
}
