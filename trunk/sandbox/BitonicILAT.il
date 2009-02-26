il_ps_2_0
dcl_output_generic o0
dcl_resource_id(0)_type(2d,unnorm)_fmtx(float)_fmty(float)_fmtz(float)_fmtw(float)
dcl_input_position_interp(linear_noperspective) v0.xy__
dcl_literal l0, 0xFFFFFFFF, 0x00000001, 0x00000000, 0xFFFFFFFF
dcl_cb cb0[4]

sample_resource(0)_sampler(0) r5, v0.xy00

ftoi r1.xy__, v0.xy00
imul r1._y__, r1.0y00, cb0[3].0x00
iadd r1.x___, r1.y000, r1.x000

;r3 = idx1 % offset_2
iadd r3.x___, cb0[2].x000, l0.x000
and r3.x___, r1.x000, r3.x000
ilt r3.x___, r3.x000, cb0[1].x000
cmov_logical r3.x___, r3.x000, l0.y000, l0.x000

ishr r4.x___, r1.x000, cb0[0].x000
and r4.x___, r4.x000, l0.y000
ieq r4.x___, r4.x000, l0.z000
cmov_logical r4.x___, r4.x000, l0.y000, l0.x000

imul r2.x___, r3.x000, cb0[1].x000
iadd r2.x___, r2.x000, r1.x000

udiv r2._y__, r2.0x00, cb0[3].0x00
imul r22.x___, r2.y000, cb0[3].x000_neg(x)
iadd r2.x___, r2.x000, r22.x000
itof r2, r2

sample_resource(0)_sampler(0) r6, r2.xy00

lt r7, r5, r6
cmov_logical r8, r7, r5, r6
cmov_logical r9, r7, r6, r5

ieq r10, r3.x000, r4.x000
cmov_logical o0.x___, r10, r8, r9

endmain
end
