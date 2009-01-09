il_ps_2_0
dcl_output_generic o0
dcl_resource_id(0)_type(1d,unnorm)_fmtx(float)_fmty(float)_fmtz(float)_fmtw(float)
dcl_input_position_interp(linear_noperspective) v0.xy__
dcl_literal l1, 0xFFFFFFFF, 0x00000001, 0x00000000, 0xFFFFFFFF
dcl_cb cb0[4]

;idx1
mov r1.xy__, v0
sample_resource(0)_sampler(0) r11, r1.x000

;idx1 mod offset_2
ftoi r1.x___, r1.x000
iadd r10.x___, cb0[2].x000, l1.x000
and r3.x___, r1.x000, r10.x000

;sign = (idx1 % offset_2) < offset
ilt r3.x___, r3.x000, cb0[1].x000
cmov_logical r3.x___, r3.x000, l1.y000, l1.x000

;(floor(idx / stageWidth) % 2)
ishr r4.x___, r1.x000, cb0[0].x000
and r4.x___, r4.x000, l1.y000

;dir = (floor(idx1 / stageWidth) % 2) == 0) ? 1 : -1
ieq r4.x___, r4.x000, l1.z000
cmov_logical r4.x___, r4.x000, l1.y000, l1.x000

imul r2.x___, r3.x000, cb0[1].x000
iadd r2.x___, r2.x000, r1.x000

itof r2.x___, r2.x000
sample_resource(0)_sampler(0) r22, r2.x000

lt r100, r11, r22
cmov_logical r5, r100, r11, r22
cmov_logical r6, r100, r22, r11

ieq r44, r3.x000, r4.x000
cmov_logical o0, r44, r5, r6
endmain
end
