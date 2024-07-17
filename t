
woody:     file format elf64-x86-64


Disassembly of section .init:

0000000000001000 <_init>:
    1000:	48 83 ec 08          	sub    $0x8,%rsp
    1004:	48 8b 05 c5 2f 00 00 	mov    0x2fc5(%rip),%rax        # 3fd0 <__gmon_start__@Base>
    100b:	48 85 c0             	test   %rax,%rax
    100e:	74 02                	je     1012 <_init+0x12>
    1010:	ff d0                	call   *%rax
    1012:	48 83 c4 08          	add    $0x8,%rsp
    1016:	c3                   	ret

Disassembly of section .plt:

0000000000001020 <write@plt-0x10>:
    1020:	ff 35 ca 2f 00 00    	push   0x2fca(%rip)        # 3ff0 <_GLOBAL_OFFSET_TABLE_+0x8>
    1026:	ff 25 cc 2f 00 00    	jmp    *0x2fcc(%rip)        # 3ff8 <_GLOBAL_OFFSET_TABLE_+0x10>
    102c:	0f 1f 40 00          	nopl   0x0(%rax)

0000000000001030 <write@plt>:
    1030:	ff 25 ca 2f 00 00    	jmp    *0x2fca(%rip)        # 4000 <write@GLIBC_2.2.5>
    1036:	68 00 00 00 00       	push   $0x0
    103b:	e9 e0 ff ff ff       	jmp    1020 <_init+0x20>

Disassembly of section .plt.got:

0000000000001040 <__cxa_finalize@plt>:
    1040:	ff 25 9a 2f 00 00    	jmp    *0x2f9a(%rip)        # 3fe0 <__cxa_finalize@GLIBC_2.2.5>
    1046:	66 90                	xchg   %ax,%ax

Disassembly of section .text:

0000000000001050 <_start>:
    1050:	31 ed                	xor    %ebp,%ebp
    1052:	49 89 d1             	mov    %rdx,%r9
    1055:	5e                   	pop    %rsi
    1056:	48 89 e2             	mov    %rsp,%rdx
    1059:	48 83 e4 f0          	and    $0xfffffffffffffff0,%rsp
    105d:	50                   	push   %rax
    105e:	54                   	push   %rsp
    105f:	45 31 c0             	xor    %r8d,%r8d
    1062:	31 c9                	xor    %ecx,%ecx
    1064:	48 8d 3d ce 00 00 00 	lea    0xce(%rip),%rdi        # 1139 <main>
    106b:	ff 15 4f 2f 00 00    	call   *0x2f4f(%rip)        # 3fc0 <__libc_start_main@GLIBC_2.34>
    1071:	f4                   	hlt
    1072:	66 2e 0f 1f 84 00 00 	cs nopw 0x0(%rax,%rax,1)
    1079:	00 00 00 
    107c:	0f 1f 40 00          	nopl   0x0(%rax)

0000000000001080 <deregister_tm_clones>:
    1080:	48 8d 3d 91 2f 00 00 	lea    0x2f91(%rip),%rdi        # 4018 <__TMC_END__>
    1087:	48 8d 05 8a 2f 00 00 	lea    0x2f8a(%rip),%rax        # 4018 <__TMC_END__>
    108e:	48 39 f8             	cmp    %rdi,%rax
    1091:	74 15                	je     10a8 <deregister_tm_clones+0x28>
    1093:	48 8b 05 2e 2f 00 00 	mov    0x2f2e(%rip),%rax        # 3fc8 <_ITM_deregisterTMCloneTable@Base>
    109a:	48 85 c0             	test   %rax,%rax
    109d:	74 09                	je     10a8 <deregister_tm_clones+0x28>
    109f:	ff e0                	jmp    *%rax
    10a1:	0f 1f 80 00 00 00 00 	nopl   0x0(%rax)
    10a8:	c3                   	ret
    10a9:	0f 1f 80 00 00 00 00 	nopl   0x0(%rax)

00000000000010b0 <register_tm_clones>:
    10b0:	48 8d 3d 61 2f 00 00 	lea    0x2f61(%rip),%rdi        # 4018 <__TMC_END__>
    10b7:	48 8d 35 5a 2f 00 00 	lea    0x2f5a(%rip),%rsi        # 4018 <__TMC_END__>
    10be:	48 29 fe             	sub    %rdi,%rsi
    10c1:	48 89 f0             	mov    %rsi,%rax
    10c4:	48 c1 ee 3f          	shr    $0x3f,%rsi
    10c8:	48 c1 f8 03          	sar    $0x3,%rax
    10cc:	48 01 c6             	add    %rax,%rsi
    10cf:	48 d1 fe             	sar    $1,%rsi
    10d2:	74 14                	je     10e8 <register_tm_clones+0x38>
    10d4:	48 8b 05 fd 2e 00 00 	mov    0x2efd(%rip),%rax        # 3fd8 <_ITM_registerTMCloneTable@Base>
    10db:	48 85 c0             	test   %rax,%rax
    10de:	74 08                	je     10e8 <register_tm_clones+0x38>
    10e0:	ff e0                	jmp    *%rax
    10e2:	66 0f 1f 44 00 00    	nopw   0x0(%rax,%rax,1)
    10e8:	c3                   	ret
    10e9:	0f 1f 80 00 00 00 00 	nopl   0x0(%rax)

00000000000010f0 <__do_global_dtors_aux>:
    10f0:	f3 0f 1e fa          	endbr64
    10f4:	80 3d 1d 2f 00 00 00 	cmpb   $0x0,0x2f1d(%rip)        # 4018 <__TMC_END__>
    10fb:	75 2b                	jne    1128 <__do_global_dtors_aux+0x38>
    10fd:	55                   	push   %rbp
    10fe:	48 83 3d da 2e 00 00 	cmpq   $0x0,0x2eda(%rip)        # 3fe0 <__cxa_finalize@GLIBC_2.2.5>
    1105:	00 
    1106:	48 89 e5             	mov    %rsp,%rbp
    1109:	74 0c                	je     1117 <__do_global_dtors_aux+0x27>
    110b:	48 8b 3d fe 2e 00 00 	mov    0x2efe(%rip),%rdi        # 4010 <__dso_handle>
    1112:	e8 29 ff ff ff       	call   1040 <__cxa_finalize@plt>
    1117:	e8 64 ff ff ff       	call   1080 <deregister_tm_clones>
    111c:	c6 05 f5 2e 00 00 01 	movb   $0x1,0x2ef5(%rip)        # 4018 <__TMC_END__>
    1123:	5d                   	pop    %rbp
    1124:	c3                   	ret
    1125:	0f 1f 00             	nopl   (%rax)
    1128:	c3                   	ret
    1129:	0f 1f 80 00 00 00 00 	nopl   0x0(%rax)

0000000000001130 <frame_dummy>:
    1130:	f3 0f 1e fa          	endbr64
    1134:	e9 77 ff ff ff       	jmp    10b0 <register_tm_clones>

0000000000001139 <main>:
    1139:	55                   	push   %rbp
    113a:	48 89 e5             	mov    %rsp,%rbp
    113d:	48 83 ec 10          	sub    $0x10,%rsp
    1141:	89 7d fc             	mov    %edi,-0x4(%rbp)
    1144:	48 89 75 f0          	mov    %rsi,-0x10(%rbp)
    1148:	ba 0c 00 00 00       	mov    $0xc,%edx
    114d:	48 8d 05 b0 0e 00 00 	lea    0xeb0(%rip),%rax        # 2004 <_IO_stdin_used+0x4>
    1154:	48 89 c6             	mov    %rax,%rsi
    1157:	bf 01 00 00 00       	mov    $0x1,%edi
    115c:	b8 00 00 00 00       	mov    $0x0,%eax
    1161:	e8 ca fe ff ff       	call   1030 <write@plt>
    1166:	b8 00 00 00 00       	mov    $0x0,%eax
    116b:	c9                   	leave
    116c:	c3                   	ret

Disassembly of section .fini:

0000000000001170 <_fini>:
    1170:	48 83 ec 08          	sub    $0x8,%rsp
    1174:	48 83 c4 08          	add    $0x8,%rsp
    1178:	c3                   	ret

Disassembly of section .i'm a teapot:

0000000000004018 <completed.0>:
    4018:	50 52 56 57 bf 00 01 00                             PRVW....

0000000000004020 <_end>:
    4020:	00 48 8b             	add    %cl,-0x75(%rax)
    4023:	05 e8 ff ff ff       	add    $0xffffffe8,%eax
    4028:	ff d0                	call   *%rax
    402a:	eb 0f                	jmp    403b <_end+0x1b>
    402c:	2e 2e 2e 2e 57       	cs cs cs cs push %rdi
    4031:	4f                   	rex.WRXB
    4032:	4f                   	rex.WRXB
    4033:	44 59                	rex.R pop %rcx
    4035:	2e 2e 2e 2e 0a 00    	cs cs cs cs or (%rax),%al
    403b:	b8 01 00 00 00       	mov    $0x1,%eax
    4040:	bf 01 00 00 00       	mov    $0x1,%edi
    4045:	48 8d 35 e0 ff ff ff 	lea    -0x20(%rip),%rsi        # 402c <_end+0xc>
    404c:	ba 0f 00 00 00       	mov    $0xf,%edx
    4051:	0f 05                	syscall
    4053:	5f                   	pop    %rdi
    4054:	5e                   	pop    %rsi
    4055:	5a                   	pop    %rdx
    4056:	58                   	pop    %rax
    4057:	90                   	nop
    4058:	90                   	nop
    4059:	90                   	nop
    405a:	90                   	nop
    405b:	90                   	nop
    405c:	90                   	nop
    405d:	90                   	nop
    405e:	90                   	nop
    405f:	90                   	nop
    4060:	90                   	nop
    4061:	90                   	nop
    4062:	90                   	nop
    4063:	90                   	nop
    4064:	90                   	nop
    4065:	90                   	nop
    4066:	90                   	nop
    4067:	90                   	nop
    4068:	90                   	nop
    4069:	90                   	nop
    406a:	90                   	nop
    406b:	90                   	nop
    406c:	90                   	nop
    406d:	90                   	nop
    406e:	90                   	nop
    406f:	90                   	nop
    4070:	90                   	nop
    4071:	90                   	nop
    4072:	90                   	nop
    4073:	90                   	nop
    4074:	90                   	nop
    4075:	90                   	nop
    4076:	90                   	nop
    4077:	90                   	nop
    4078:	90                   	nop
    4079:	90                   	nop
    407a:	90                   	nop
    407b:	90                   	nop
    407c:	90                   	nop
    407d:	90                   	nop
    407e:	90                   	nop
    407f:	90                   	nop
    4080:	90                   	nop
    4081:	90                   	nop
    4082:	90                   	nop
    4083:	90                   	nop
    4084:	90                   	nop
    4085:	90                   	nop
    4086:	90                   	nop
    4087:	90                   	nop
    4088:	90                   	nop
    4089:	90                   	nop
    408a:	90                   	nop
    408b:	90                   	nop
    408c:	90                   	nop
    408d:	90                   	nop
    408e:	90                   	nop
    408f:	90                   	nop
    4090:	90                   	nop
    4091:	90                   	nop
    4092:	90                   	nop
    4093:	90                   	nop
    4094:	90                   	nop
    4095:	90                   	nop
    4096:	90                   	nop
    4097:	90                   	nop
    4098:	90                   	nop
    4099:	90                   	nop
    409a:	90                   	nop
    409b:	90                   	nop
    409c:	90                   	nop
    409d:	90                   	nop
    409e:	90                   	nop
    409f:	90                   	nop
    40a0:	90                   	nop
    40a1:	90                   	nop
    40a2:	90                   	nop
    40a3:	90                   	nop
    40a4:	90                   	nop
    40a5:	90                   	nop
    40a6:	90                   	nop
    40a7:	90                   	nop
    40a8:	90                   	nop
    40a9:	90                   	nop
    40aa:	90                   	nop
    40ab:	90                   	nop
    40ac:	90                   	nop
    40ad:	90                   	nop
    40ae:	90                   	nop
    40af:	90                   	nop
    40b0:	90                   	nop
    40b1:	90                   	nop
    40b2:	90                   	nop
    40b3:	90                   	nop
    40b4:	90                   	nop
    40b5:	90                   	nop
    40b6:	90                   	nop
    40b7:	90                   	nop
    40b8:	90                   	nop
    40b9:	90                   	nop
    40ba:	90                   	nop
    40bb:	90                   	nop
    40bc:	90                   	nop
    40bd:	90                   	nop
    40be:	90                   	nop
    40bf:	90                   	nop
    40c0:	90                   	nop
    40c1:	90                   	nop
    40c2:	90                   	nop
    40c3:	90                   	nop
    40c4:	90                   	nop
    40c5:	90                   	nop
    40c6:	90                   	nop
    40c7:	90                   	nop
    40c8:	90                   	nop
    40c9:	90                   	nop
    40ca:	90                   	nop
    40cb:	90                   	nop
    40cc:	90                   	nop
    40cd:	90                   	nop
    40ce:	90                   	nop
    40cf:	90                   	nop
    40d0:	90                   	nop
    40d1:	90                   	nop
    40d2:	90                   	nop
    40d3:	90                   	nop
    40d4:	90                   	nop
    40d5:	90                   	nop
    40d6:	90                   	nop
    40d7:	90                   	nop
    40d8:	90                   	nop
    40d9:	90                   	nop
    40da:	90                   	nop
    40db:	90                   	nop
    40dc:	90                   	nop
    40dd:	90                   	nop
    40de:	90                   	nop
    40df:	90                   	nop
    40e0:	90                   	nop
    40e1:	90                   	nop
    40e2:	90                   	nop
    40e3:	90                   	nop
    40e4:	90                   	nop
    40e5:	90                   	nop
    40e6:	90                   	nop
    40e7:	90                   	nop
    40e8:	90                   	nop
    40e9:	90                   	nop
    40ea:	90                   	nop
    40eb:	90                   	nop
    40ec:	90                   	nop
    40ed:	90                   	nop
    40ee:	90                   	nop
    40ef:	90                   	nop
    40f0:	90                   	nop
    40f1:	90                   	nop
    40f2:	90                   	nop
    40f3:	90                   	nop
    40f4:	90                   	nop
    40f5:	90                   	nop
    40f6:	90                   	nop
    40f7:	90                   	nop
    40f8:	90                   	nop
    40f9:	90                   	nop
    40fa:	90                   	nop
    40fb:	90                   	nop
    40fc:	90                   	nop
    40fd:	90                   	nop
    40fe:	90                   	nop
    40ff:	90                   	nop
    4100:	90                   	nop
    4101:	90                   	nop
    4102:	90                   	nop
    4103:	90                   	nop
    4104:	90                   	nop
    4105:	90                   	nop
    4106:	90                   	nop
    4107:	90                   	nop
    4108:	90                   	nop
    4109:	90                   	nop
    410a:	90                   	nop
    410b:	90                   	nop
    410c:	90                   	nop
    410d:	90                   	nop
    410e:	90                   	nop
    410f:	90                   	nop
    4110:	04 05                	add    $0x5,%al
    4112:	06                   	(bad)
    4113:	07                   	(bad)
    4114:	08 09                	or     %cl,(%rcx)
    4116:	0a 0b                	or     (%rbx),%cl
    4118:	08 09                	or     %cl,(%rcx)
    411a:	0a 0b                	or     (%rbx),%cl
    411c:	0c 0d                	or     $0xd,%al
    411e:	0e                   	(bad)
    411f:	0f 90 90 90 90 90 90 	seto   -0x6f6f6f70(%rax)
    4126:	90                   	nop
    4127:	90                   	nop
    4128:	90                   	nop
    4129:	90                   	nop
    412a:	90                   	nop
    412b:	90                   	nop
    412c:	90                   	nop
    412d:	90                   	nop
    412e:	90                   	nop
    412f:	90                   	nop
    4130:	90                   	nop
    4131:	90                   	nop
    4132:	90                   	nop
    4133:	90                   	nop
    4134:	90                   	nop
    4135:	90                   	nop
    4136:	90                   	nop
    4137:	90                   	nop
    4138:	90                   	nop
    4139:	90                   	nop
    413a:	90                   	nop
    413b:	90                   	nop
    413c:	90                   	nop
    413d:	90                   	nop
    413e:	90                   	nop
    413f:	90                   	nop
    4140:	90                   	nop
    4141:	90                   	nop
    4142:	90                   	nop
    4143:	90                   	nop
    4144:	90                   	nop
    4145:	90                   	nop
    4146:	90                   	nop
    4147:	90                   	nop
    4148:	90                   	nop
    4149:	90                   	nop
    414a:	90                   	nop
    414b:	90                   	nop
    414c:	90                   	nop
    414d:	90                   	nop
    414e:	90                   	nop
    414f:	90                   	nop
    4150:	90                   	nop
    4151:	90                   	nop
    4152:	90                   	nop
    4153:	90                   	nop
    4154:	90                   	nop
    4155:	90                   	nop
    4156:	90                   	nop
    4157:	90                   	nop
    4158:	90                   	nop
    4159:	90                   	nop
    415a:	90                   	nop
    415b:	90                   	nop
    415c:	90                   	nop
    415d:	90                   	nop
    415e:	90                   	nop
    415f:	90                   	nop
    4160:	90                   	nop
    4161:	90                   	nop
    4162:	90                   	nop
    4163:	90                   	nop
    4164:	90                   	nop
    4165:	90                   	nop
    4166:	90                   	nop
    4167:	90                   	nop
    4168:	90                   	nop
    4169:	90                   	nop
    416a:	90                   	nop
    416b:	90                   	nop
    416c:	90                   	nop
    416d:	90                   	nop
    416e:	90                   	nop
    416f:	90                   	nop
    4170:	90                   	nop
    4171:	90                   	nop
    4172:	90                   	nop
    4173:	90                   	nop
    4174:	90                   	nop
    4175:	90                   	nop
    4176:	90                   	nop
    4177:	90                   	nop
    4178:	90                   	nop
    4179:	90                   	nop
    417a:	90                   	nop
    417b:	90                   	nop
    417c:	90                   	nop
    417d:	90                   	nop
    417e:	90                   	nop
    417f:	90                   	nop
    4180:	90                   	nop
    4181:	90                   	nop
    4182:	90                   	nop
    4183:	90                   	nop
    4184:	90                   	nop
    4185:	90                   	nop
    4186:	90                   	nop
    4187:	90                   	nop
    4188:	90                   	nop
    4189:	90                   	nop
    418a:	90                   	nop
    418b:	90                   	nop
    418c:	90                   	nop
    418d:	90                   	nop
    418e:	90                   	nop
    418f:	90                   	nop
    4190:	90                   	nop
    4191:	90                   	nop
    4192:	90                   	nop
    4193:	90                   	nop
    4194:	90                   	nop
    4195:	90                   	nop
    4196:	90                   	nop
    4197:	90                   	nop
    4198:	90                   	nop
    4199:	90                   	nop
    419a:	90                   	nop
    419b:	90                   	nop
    419c:	90                   	nop
    419d:	90                   	nop
    419e:	90                   	nop
    419f:	90                   	nop
    41a0:	90                   	nop
    41a1:	90                   	nop
    41a2:	90                   	nop
    41a3:	90                   	nop
    41a4:	90                   	nop
    41a5:	90                   	nop
    41a6:	90                   	nop
    41a7:	90                   	nop
    41a8:	90                   	nop
    41a9:	90                   	nop
    41aa:	90                   	nop
    41ab:	90                   	nop
    41ac:	90                   	nop
    41ad:	90                   	nop
    41ae:	90                   	nop
    41af:	90                   	nop
    41b0:	90                   	nop
    41b1:	90                   	nop
    41b2:	90                   	nop
    41b3:	90                   	nop
    41b4:	90                   	nop
    41b5:	90                   	nop
    41b6:	90                   	nop
    41b7:	90                   	nop
    41b8:	90                   	nop
    41b9:	90                   	nop
    41ba:	90                   	nop
    41bb:	90                   	nop
    41bc:	90                   	nop
    41bd:	90                   	nop
    41be:	90                   	nop
    41bf:	90                   	nop
    41c0:	90                   	nop
    41c1:	90                   	nop
    41c2:	90                   	nop
    41c3:	90                   	nop
    41c4:	90                   	nop
    41c5:	90                   	nop
    41c6:	90                   	nop
    41c7:	90                   	nop
    41c8:	90                   	nop
    41c9:	90                   	nop
    41ca:	90                   	nop
    41cb:	90                   	nop
    41cc:	90                   	nop
    41cd:	90                   	nop
    41ce:	90                   	nop
    41cf:	90                   	nop
    41d0:	90                   	nop
    41d1:	90                   	nop
    41d2:	90                   	nop
    41d3:	90                   	nop
    41d4:	90                   	nop
    41d5:	90                   	nop
    41d6:	90                   	nop
    41d7:	90                   	nop
    41d8:	90                   	nop
    41d9:	90                   	nop
    41da:	90                   	nop
    41db:	90                   	nop
    41dc:	90                   	nop
    41dd:	90                   	nop
    41de:	90                   	nop
    41df:	90                   	nop
    41e0:	90                   	nop
    41e1:	90                   	nop
    41e2:	90                   	nop
    41e3:	90                   	nop
    41e4:	90                   	nop
    41e5:	90                   	nop
    41e6:	90                   	nop
    41e7:	90                   	nop
    41e8:	90                   	nop
    41e9:	90                   	nop
    41ea:	90                   	nop
    41eb:	90                   	nop
    41ec:	90                   	nop
    41ed:	90                   	nop
    41ee:	90                   	nop
    41ef:	90                   	nop
    41f0:	90                   	nop
    41f1:	90                   	nop
    41f2:	90                   	nop
    41f3:	90                   	nop
    41f4:	90                   	nop
    41f5:	90                   	nop
    41f6:	90                   	nop
    41f7:	90                   	nop
    41f8:	90                   	nop
    41f9:	90                   	nop
    41fa:	90                   	nop
    41fb:	90                   	nop
    41fc:	90                   	nop
    41fd:	90                   	nop
    41fe:	90                   	nop
    41ff:	90                   	nop
    4200:	90                   	nop
    4201:	90                   	nop
    4202:	90                   	nop
    4203:	90                   	nop
    4204:	90                   	nop
    4205:	90                   	nop
    4206:	90                   	nop
    4207:	90                   	nop
    4208:	90                   	nop
    4209:	90                   	nop
    420a:	90                   	nop
    420b:	90                   	nop
    420c:	90                   	nop
    420d:	90                   	nop
    420e:	90                   	nop
    420f:	90                   	nop
    4210:	07                   	(bad)
    4211:	06                   	(bad)
    4212:	05 04 03 02 01       	add    $0x1020304,%eax
    4217:	00 0f                	add    %cl,(%rdi)
    4219:	0e                   	(bad)
    421a:	0d 0c 0b 0a 09       	or     $0x90a0b0c,%eax
    421f:	08 4d 89             	or     %cl,-0x77(%rbp)
    4222:	c2 44 8b             	ret    $0x8b44
    4225:	64 24 08             	fs and $0x8,%al
    4228:	49 c1 e8 04          	shr    $0x4,%r8
    422c:	49 c1 e2 3c          	shl    $0x3c,%r10
    4230:	74 04                	je     4236 <_end+0x216>
    4232:	49 83 c0 01          	add    $0x1,%r8
    4236:	4d 89 c2             	mov    %r8,%r10
    4239:	49 c1 e2 3e          	shl    $0x3e,%r10
    423d:	49 c1 ea 3e          	shr    $0x3e,%r10
    4241:	66 48 0f 3a 22 02 01 	pinsrq $0x1,(%rdx),%xmm0
    4248:	66 0f 3a 22 01 01    	pinsrd $0x1,(%rcx),%xmm0
    424e:	66 0f 73 d8 04       	psrldq $0x4,%xmm0
    4253:	66 0f 6f d0          	movdqa %xmm0,%xmm2
    4257:	66 0f 38 00 15 b0 fe 	pshufb -0x150(%rip),%xmm2        # 4110 <_end+0xf0>
    425e:	ff ff 
    4260:	66 0f d4 15 a8 fe ff 	paddq  -0x158(%rip),%xmm2        # 4110 <_end+0xf0>
    4267:	ff 
    4268:	66 0f 6f ca          	movdqa %xmm2,%xmm1
    426c:	66 0f d4 15 9c fe ff 	paddq  -0x164(%rip),%xmm2        # 4110 <_end+0xf0>
    4273:	ff 
    4274:	66 0f 38 00 0d 93 ff 	pshufb -0x6d(%rip),%xmm1        # 4210 <_end+0x1f0>
    427b:	ff ff 
    427d:	66 0f 38 00 15 8a ff 	pshufb -0x76(%rip),%xmm2        # 4210 <_end+0x1f0>
    4284:	ff ff 
    4286:	49 c1 e8 02          	shr    $0x2,%r8
    428a:	0f 84 a3 02 00 00    	je     4533 <_end+0x513>
    4290:	48 83 ee 40          	sub    $0x40,%rsi
    4294:	48 83 ef 40          	sub    $0x40,%rdi
    4298:	48 83 c6 40          	add    $0x40,%rsi
    429c:	48 83 c7 40          	add    $0x40,%rdi
    42a0:	66 44 0f 6f d8       	movdqa %xmm0,%xmm11
    42a5:	66 44 0f 6f e0       	movdqa %xmm0,%xmm12
    42aa:	66 44 0f 6f e8       	movdqa %xmm0,%xmm13
    42af:	66 44 0f 6f f0       	movdqa %xmm0,%xmm14
    42b4:	66 44 0f c6 d9 02    	shufpd $0x2,%xmm1,%xmm11
    42ba:	66 44 0f c6 e1 00    	shufpd $0x0,%xmm1,%xmm12
    42c0:	66 44 0f c6 ea 02    	shufpd $0x2,%xmm2,%xmm13
    42c6:	66 44 0f c6 f2 00    	shufpd $0x0,%xmm2,%xmm14
    42cc:	66 0f 38 00 0d 3b ff 	pshufb -0xc5(%rip),%xmm1        # 4210 <_end+0x1f0>
    42d3:	ff ff 
    42d5:	66 0f 38 00 15 32 ff 	pshufb -0xce(%rip),%xmm2        # 4210 <_end+0x1f0>
    42dc:	ff ff 
    42de:	66 45 0f 6f 01       	movdqa (%r9),%xmm8
    42e3:	66 45 0f 6f 49 10    	movdqa 0x10(%r9),%xmm9
    42e9:	66 45 0f 6f 51 20    	movdqa 0x20(%r9),%xmm10
    42ef:	66 41 0f 6f 79 30    	movdqa 0x30(%r9),%xmm7
    42f5:	66 0f d4 0d 13 fe ff 	paddq  -0x1ed(%rip),%xmm1        # 4110 <_end+0xf0>
    42fc:	ff 
    42fd:	66 0f d4 15 0b fe ff 	paddq  -0x1f5(%rip),%xmm2        # 4110 <_end+0xf0>
    4304:	ff 
    4305:	66 45 0f ef d8       	pxor   %xmm8,%xmm11
    430a:	66 45 0f ef e0       	pxor   %xmm8,%xmm12
    430f:	66 45 0f ef e8       	pxor   %xmm8,%xmm13
    4314:	66 45 0f ef f0       	pxor   %xmm8,%xmm14
    4319:	66 0f 38 00 0d ee fe 	pshufb -0x112(%rip),%xmm1        # 4210 <_end+0x1f0>
    4320:	ff ff 
    4322:	66 0f 38 00 15 e5 fe 	pshufb -0x11b(%rip),%xmm2        # 4210 <_end+0x1f0>
    4329:	ff ff 
    432b:	66 45 0f 38 dc d9    	aesenc %xmm9,%xmm11
    4331:	66 45 0f 38 dc e1    	aesenc %xmm9,%xmm12
    4337:	66 45 0f 38 dc e9    	aesenc %xmm9,%xmm13
    433d:	66 45 0f 38 dc f1    	aesenc %xmm9,%xmm14
    4343:	66 45 0f 38 dc da    	aesenc %xmm10,%xmm11
    4349:	66 45 0f 38 dc e2    	aesenc %xmm10,%xmm12
    434f:	66 45 0f 38 dc ea    	aesenc %xmm10,%xmm13
    4355:	66 45 0f 38 dc f2    	aesenc %xmm10,%xmm14
    435b:	66 44 0f 38 dc df    	aesenc %xmm7,%xmm11
    4361:	66 44 0f 38 dc e7    	aesenc %xmm7,%xmm12
    4367:	66 44 0f 38 dc ef    	aesenc %xmm7,%xmm13
    436d:	66 44 0f 38 dc f7    	aesenc %xmm7,%xmm14
    4373:	66 45 0f 6f 41 40    	movdqa 0x40(%r9),%xmm8
    4379:	66 45 0f 6f 49 50    	movdqa 0x50(%r9),%xmm9
    437f:	66 45 0f 6f 51 60    	movdqa 0x60(%r9),%xmm10
    4385:	66 41 0f 6f 79 70    	movdqa 0x70(%r9),%xmm7
    438b:	66 45 0f 38 dc d8    	aesenc %xmm8,%xmm11
    4391:	66 45 0f 38 dc e0    	aesenc %xmm8,%xmm12
    4397:	66 45 0f 38 dc e8    	aesenc %xmm8,%xmm13
    439d:	66 45 0f 38 dc f0    	aesenc %xmm8,%xmm14
    43a3:	66 45 0f 38 dc d9    	aesenc %xmm9,%xmm11
    43a9:	66 45 0f 38 dc e1    	aesenc %xmm9,%xmm12
    43af:	66 45 0f 38 dc e9    	aesenc %xmm9,%xmm13
    43b5:	66 45 0f 38 dc f1    	aesenc %xmm9,%xmm14
    43bb:	66 45 0f 38 dc da    	aesenc %xmm10,%xmm11
    43c1:	66 45 0f 38 dc e2    	aesenc %xmm10,%xmm12
    43c7:	66 45 0f 38 dc ea    	aesenc %xmm10,%xmm13
    43cd:	66 45 0f 38 dc f2    	aesenc %xmm10,%xmm14
    43d3:	66 44 0f 38 dc df    	aesenc %xmm7,%xmm11
    43d9:	66 44 0f 38 dc e7    	aesenc %xmm7,%xmm12
    43df:	66 44 0f 38 dc ef    	aesenc %xmm7,%xmm13
    43e5:	66 44 0f 38 dc f7    	aesenc %xmm7,%xmm14
    43eb:	66 45 0f 6f 81 80 00 	movdqa 0x80(%r9),%xmm8
    43f2:	00 00 
    43f4:	66 45 0f 6f 89 90 00 	movdqa 0x90(%r9),%xmm9
    43fb:	00 00 
    43fd:	66 45 0f 6f 91 a0 00 	movdqa 0xa0(%r9),%xmm10
    4404:	00 00 
    4406:	41 83 fc 0c          	cmp    $0xc,%r12d
    440a:	66 45 0f 38 dc d8    	aesenc %xmm8,%xmm11
    4410:	66 45 0f 38 dc e0    	aesenc %xmm8,%xmm12
    4416:	66 45 0f 38 dc e8    	aesenc %xmm8,%xmm13
    441c:	66 45 0f 38 dc f0    	aesenc %xmm8,%xmm14
    4422:	66 45 0f 38 dc d9    	aesenc %xmm9,%xmm11
    4428:	66 45 0f 38 dc e1    	aesenc %xmm9,%xmm12
    442e:	66 45 0f 38 dc e9    	aesenc %xmm9,%xmm13
    4434:	66 45 0f 38 dc f1    	aesenc %xmm9,%xmm14
    443a:	0f 82 9c 00 00 00    	jb     44dc <_end+0x4bc>
    4440:	66 45 0f 6f 81 a0 00 	movdqa 0xa0(%r9),%xmm8
    4447:	00 00 
    4449:	66 45 0f 6f 89 b0 00 	movdqa 0xb0(%r9),%xmm9
    4450:	00 00 
    4452:	66 45 0f 6f 91 c0 00 	movdqa 0xc0(%r9),%xmm10
    4459:	00 00 
    445b:	41 83 fc 0e          	cmp    $0xe,%r12d
    445f:	66 45 0f 38 dc d8    	aesenc %xmm8,%xmm11
    4465:	66 45 0f 38 dc e0    	aesenc %xmm8,%xmm12
    446b:	66 45 0f 38 dc e8    	aesenc %xmm8,%xmm13
    4471:	66 45 0f 38 dc f0    	aesenc %xmm8,%xmm14
    4477:	66 45 0f 38 dc d9    	aesenc %xmm9,%xmm11
    447d:	66 45 0f 38 dc e1    	aesenc %xmm9,%xmm12
    4483:	66 45 0f 38 dc e9    	aesenc %xmm9,%xmm13
    4489:	66 45 0f 38 dc f1    	aesenc %xmm9,%xmm14
    448f:	72 4b                	jb     44dc <_end+0x4bc>
    4491:	66 45 0f 6f 81 c0 00 	movdqa 0xc0(%r9),%xmm8
    4498:	00 00 
    449a:	66 45 0f 6f 89 d0 00 	movdqa 0xd0(%r9),%xmm9
    44a1:	00 00 
    44a3:	66 45 0f 6f 91 e0 00 	movdqa 0xe0(%r9),%xmm10
    44aa:	00 00 
    44ac:	66 45 0f 38 dc d8    	aesenc %xmm8,%xmm11
    44b2:	66 45 0f 38 dc e0    	aesenc %xmm8,%xmm12
    44b8:	66 45 0f 38 dc e8    	aesenc %xmm8,%xmm13
    44be:	66 45 0f 38 dc f0    	aesenc %xmm8,%xmm14
    44c4:	66 45 0f 38 dc d9    	aesenc %xmm9,%xmm11
    44ca:	66 45 0f 38 dc e1    	aesenc %xmm9,%xmm12
    44d0:	66 45 0f 38 dc e9    	aesenc %xmm9,%xmm13
    44d6:	66 45 0f 38 dc f1    	aesenc %xmm9,%xmm14
    44dc:	66 45 0f 38 dd da    	aesenclast %xmm10,%xmm11
    44e2:	66 45 0f 38 dd e2    	aesenclast %xmm10,%xmm12
    44e8:	66 45 0f 38 dd ea    	aesenclast %xmm10,%xmm13
    44ee:	66 45 0f 38 dd f2    	aesenclast %xmm10,%xmm14
    44f4:	66 44 0f ef 1f       	pxor   (%rdi),%xmm11
    44f9:	66 44 0f ef 67 10    	pxor   0x10(%rdi),%xmm12
    44ff:	66 44 0f ef 6f 20    	pxor   0x20(%rdi),%xmm13
    4505:	66 44 0f ef 77 30    	pxor   0x30(%rdi),%xmm14
    450b:	f3 44 0f 7f 1e       	movdqu %xmm11,(%rsi)
    4510:	f3 44 0f 7f 66 10    	movdqu %xmm12,0x10(%rsi)
    4516:	f3 44 0f 7f 6e 20    	movdqu %xmm13,0x20(%rsi)
    451c:	f3 44 0f 7f 76 30    	movdqu %xmm14,0x30(%rsi)
    4522:	49 ff c8             	dec    %r8
    4525:	0f 85 6d fd ff ff    	jne    4298 <_end+0x278>
    452b:	48 83 c6 40          	add    $0x40,%rsi
    452f:	48 83 c7 40          	add    $0x40,%rdi
    4533:	49 83 fa 00          	cmp    $0x0,%r10
    4537:	0f 84 de 00 00 00    	je     461b <_end+0x5fb>
    453d:	66 0f c6 c1 02       	shufpd $0x2,%xmm1,%xmm0
    4542:	66 44 0f 6f d8       	movdqa %xmm0,%xmm11
    4547:	66 0f 38 00 05 c0 fc 	pshufb -0x340(%rip),%xmm0        # 4210 <_end+0x1f0>
    454e:	ff ff 
    4550:	66 45 0f ef 19       	pxor   (%r9),%xmm11
    4555:	66 0f d4 05 b3 fb ff 	paddq  -0x44d(%rip),%xmm0        # 4110 <_end+0xf0>
    455c:	ff 
    455d:	66 45 0f 38 dc 59 10 	aesenc 0x10(%r9),%xmm11
    4564:	66 45 0f 38 dc 59 20 	aesenc 0x20(%r9),%xmm11
    456b:	66 0f 38 00 05 9c fc 	pshufb -0x364(%rip),%xmm0        # 4210 <_end+0x1f0>
    4572:	ff ff 
    4574:	66 45 0f 38 dc 59 30 	aesenc 0x30(%r9),%xmm11
    457b:	66 45 0f 38 dc 59 40 	aesenc 0x40(%r9),%xmm11
    4582:	66 45 0f 38 dc 59 50 	aesenc 0x50(%r9),%xmm11
    4589:	66 45 0f 38 dc 59 60 	aesenc 0x60(%r9),%xmm11
    4590:	66 45 0f 38 dc 59 70 	aesenc 0x70(%r9),%xmm11
    4597:	66 45 0f 38 dc 99 80 	aesenc 0x80(%r9),%xmm11
    459e:	00 00 00 
    45a1:	66 45 0f 38 dc 99 90 	aesenc 0x90(%r9),%xmm11
    45a8:	00 00 00 
    45ab:	66 41 0f 6f 91 a0 00 	movdqa 0xa0(%r9),%xmm2
    45b2:	00 00 
    45b4:	41 83 fc 0c          	cmp    $0xc,%r12d
    45b8:	72 40                	jb     45fa <_end+0x5da>
    45ba:	66 45 0f 38 dc 99 a0 	aesenc 0xa0(%r9),%xmm11
    45c1:	00 00 00 
    45c4:	66 45 0f 38 dc 99 b0 	aesenc 0xb0(%r9),%xmm11
    45cb:	00 00 00 
    45ce:	66 41 0f 6f 91 c0 00 	movdqa 0xc0(%r9),%xmm2
    45d5:	00 00 
    45d7:	41 83 fc 0e          	cmp    $0xe,%r12d
    45db:	72 1d                	jb     45fa <_end+0x5da>
    45dd:	66 45 0f 38 dc 99 c0 	aesenc 0xc0(%r9),%xmm11
    45e4:	00 00 00 
    45e7:	66 45 0f 38 dc 99 d0 	aesenc 0xd0(%r9),%xmm11
    45ee:	00 00 00 
    45f1:	66 41 0f 6f 91 e0 00 	movdqa 0xe0(%r9),%xmm2
    45f8:	00 00 
    45fa:	66 44 0f 38 dd da    	aesenclast %xmm2,%xmm11
    4600:	66 44 0f ef 1f       	pxor   (%rdi),%xmm11
    4605:	f3 44 0f 7f 1e       	movdqu %xmm11,(%rsi)
    460a:	48 83 c7 10          	add    $0x10,%rdi
    460e:	48 83 c6 10          	add    $0x10,%rsi
    4612:	49 ff ca             	dec    %r10
    4615:	0f 85 27 ff ff ff    	jne    4542 <_end+0x522>
    461b:	c3                   	ret
    461c:	f3 0f 6f 0f          	movdqu (%rdi),%xmm1
    4620:	f3 0f 6f 5f 10       	movdqu 0x10(%rdi),%xmm3
    4625:	66 0f 7f 0e          	movdqa %xmm1,(%rsi)
    4629:	66 0f 7f 5e 10       	movdqa %xmm3,0x10(%rsi)
    462e:	66 0f 3a df d3 01    	aeskeygenassist $0x1,%xmm3,%xmm2
    4634:	e8 db 00 00 00       	call   4714 <_end+0x6f4>
    4639:	66 0f 7f 4e 20       	movdqa %xmm1,0x20(%rsi)
    463e:	66 0f 3a df d1 00    	aeskeygenassist $0x0,%xmm1,%xmm2
    4644:	e8 f4 00 00 00       	call   473d <_end+0x71d>
    4649:	66 0f 7f 5e 30       	movdqa %xmm3,0x30(%rsi)
    464e:	66 0f 3a df d3 02    	aeskeygenassist $0x2,%xmm3,%xmm2
    4654:	e8 bb 00 00 00       	call   4714 <_end+0x6f4>
    4659:	66 0f 7f 4e 40       	movdqa %xmm1,0x40(%rsi)
    465e:	66 0f 3a df d1 00    	aeskeygenassist $0x0,%xmm1,%xmm2
    4664:	e8 d4 00 00 00       	call   473d <_end+0x71d>
    4669:	66 0f 7f 5e 50       	movdqa %xmm3,0x50(%rsi)
    466e:	66 0f 3a df d3 04    	aeskeygenassist $0x4,%xmm3,%xmm2
    4674:	e8 9b 00 00 00       	call   4714 <_end+0x6f4>
    4679:	66 0f 7f 4e 60       	movdqa %xmm1,0x60(%rsi)
    467e:	66 0f 3a df d1 00    	aeskeygenassist $0x0,%xmm1,%xmm2
    4684:	e8 b4 00 00 00       	call   473d <_end+0x71d>
    4689:	66 0f 7f 5e 70       	movdqa %xmm3,0x70(%rsi)
    468e:	66 0f 3a df d3 08    	aeskeygenassist $0x8,%xmm3,%xmm2
    4694:	e8 7b 00 00 00       	call   4714 <_end+0x6f4>
    4699:	66 0f 7f 8e 80 00 00 	movdqa %xmm1,0x80(%rsi)
    46a0:	00 
    46a1:	66 0f 3a df d1 00    	aeskeygenassist $0x0,%xmm1,%xmm2
    46a7:	e8 91 00 00 00       	call   473d <_end+0x71d>
    46ac:	66 0f 7f 9e 90 00 00 	movdqa %xmm3,0x90(%rsi)
    46b3:	00 
    46b4:	66 0f 3a df d3 10    	aeskeygenassist $0x10,%xmm3,%xmm2
    46ba:	e8 55 00 00 00       	call   4714 <_end+0x6f4>
    46bf:	66 0f 7f 8e a0 00 00 	movdqa %xmm1,0xa0(%rsi)
    46c6:	00 
    46c7:	66 0f 3a df d1 00    	aeskeygenassist $0x0,%xmm1,%xmm2
    46cd:	e8 6b 00 00 00       	call   473d <_end+0x71d>
    46d2:	66 0f 7f 9e b0 00 00 	movdqa %xmm3,0xb0(%rsi)
    46d9:	00 
    46da:	66 0f 3a df d3 20    	aeskeygenassist $0x20,%xmm3,%xmm2
    46e0:	e8 2f 00 00 00       	call   4714 <_end+0x6f4>
    46e5:	66 0f 7f 8e c0 00 00 	movdqa %xmm1,0xc0(%rsi)
    46ec:	00 
    46ed:	66 0f 3a df d1 00    	aeskeygenassist $0x0,%xmm1,%xmm2
    46f3:	e8 45 00 00 00       	call   473d <_end+0x71d>
    46f8:	66 0f 7f 9e d0 00 00 	movdqa %xmm3,0xd0(%rsi)
    46ff:	00 
    4700:	66 0f 3a df d3 40    	aeskeygenassist $0x40,%xmm3,%xmm2
    4706:	e8 09 00 00 00       	call   4714 <_end+0x6f4>
    470b:	66 0f 7f 8e e0 00 00 	movdqa %xmm1,0xe0(%rsi)
    4712:	00 
    4713:	c3                   	ret
    4714:	66 0f 70 d2 ff       	pshufd $0xff,%xmm2,%xmm2
    4719:	66 0f 6f e1          	movdqa %xmm1,%xmm4
    471d:	66 0f 73 fc 04       	pslldq $0x4,%xmm4
    4722:	66 0f ef cc          	pxor   %xmm4,%xmm1
    4726:	66 0f 73 fc 04       	pslldq $0x4,%xmm4
    472b:	66 0f ef cc          	pxor   %xmm4,%xmm1
    472f:	66 0f 73 fc 04       	pslldq $0x4,%xmm4
    4734:	66 0f ef cc          	pxor   %xmm4,%xmm1
    4738:	66 0f ef ca          	pxor   %xmm2,%xmm1
    473c:	c3                   	ret
    473d:	66 0f 70 d2 aa       	pshufd $0xaa,%xmm2,%xmm2
    4742:	66 0f 6f e3          	movdqa %xmm3,%xmm4
    4746:	66 0f 73 fc 04       	pslldq $0x4,%xmm4
    474b:	66 0f ef dc          	pxor   %xmm4,%xmm3
    474f:	66 0f 73 fc 04       	pslldq $0x4,%xmm4
    4754:	66 0f ef dc          	pxor   %xmm4,%xmm3
    4758:	66 0f 73 fc 04       	pslldq $0x4,%xmm4
    475d:	66 0f ef dc          	pxor   %xmm4,%xmm3
    4761:	66 ea                	data16 (bad)
    4763:	c8 ff ff ff          	enter  $0xffff,$0xff
    4767:	ff                   	(bad)
    4768:	ff                   	(bad)
    4769:	ff 34 35 36 37 38 39 	push   0x39383736(,%rsi,1)
    4770:	61                   	(bad)
    4771:	62 63 64 65 66       	(bad)
    4776:	30 31                	xor    %dh,(%rcx)
    4778:	32 33                	xor    (%rbx),%dh
    477a:	34 35                	xor    $0x35,%al
    477c:	36 37                	ss (bad)
    477e:	38 39                	cmp    %bh,(%rcx)
    4780:	61                   	(bad)
    4781:	62 63 64 65 66       	(bad)
    4786:	30 31                	xor    %dh,(%rcx)
    4788:	32 33                	xor    (%rbx),%dh
    478a:	34 35                	xor    $0x35,%al
    478c:	36 37                	ss (bad)
    478e:	38 39                	cmp    %bh,(%rcx)
    4790:	61                   	(bad)
    4791:	62 63 64 65 66       	(bad)
    4796:	30 31                	xor    %dh,(%rcx)
    4798:	32 33                	xor    (%rbx),%dh
    479a:	34 35                	xor    $0x35,%al
    479c:	36 37                	ss (bad)
    479e:	38 39                	cmp    %bh,(%rcx)
    47a0:	61                   	(bad)
    47a1:	62 63 64 65 66       	(bad)
    47a6:	bb bb bb bb bb       	mov    $0xbbbbbbbb,%ebx
    47ab:	bb bb bb cc cc       	mov    $0xccccbbbb,%ebx
    47b0:	cc                   	int3
    47b1:	cc                   	int3
    47b2:	cc                   	int3
    47b3:	cc                   	int3
    47b4:	cc                   	int3
    47b5:	cc                   	int3
    47b6:	dd dd                	fstp   %st(5)
    47b8:	dd dd                	fstp   %st(5)
    47ba:	dd dd                	fstp   %st(5)
    47bc:	dd dd                	fstp   %st(5)
    47be:	62 62 62 62 62       	(bad)
    47c3:	62 62 62 62 62       	(bad)
    47c8:	62 62 62 62 62       	(bad)
    47cd:	62 62 62 62 62       	(bad)
    47d2:	62 62 62 62 62       	(bad)
    47d7:	62 62 62 62 62       	(bad)
    47dc:	62 62 62 62 62       	(bad)
    47e1:	62 62 62 62 62       	(bad)
    47e6:	62 62 62 62 62       	(bad)
    47eb:	62 62 62 62 62       	(bad)
    47f0:	62 62 62 62 62       	(bad)
    47f5:	62 62 62 62 62       	(bad)
    47fa:	62 62 62 62 62       	(bad)
    47ff:	62 62 62 62 62       	(bad)
    4804:	62 62 62 62 62       	(bad)
    4809:	62 62 62 62 62       	(bad)
    480e:	62 62 62 62 62       	(bad)
    4813:	62 62 62 62 62       	(bad)
    4818:	62 62 62 62 62       	(bad)
    481d:	62 62 62 62 62       	(bad)
    4822:	62 62 62 62 62       	(bad)
    4827:	62 62 62 62 62       	(bad)
    482c:	62 62 62 62 62       	(bad)
    4831:	62 62 62 62 62       	(bad)
    4836:	62 62 62 62 62       	(bad)
    483b:	62 62 62 62 62       	(bad)
    4840:	62 62 62 62 62       	(bad)
    4845:	62 62 62 62 62       	(bad)
    484a:	62 62 62 62 62       	(bad)
    484f:	62 62 62 62 62       	(bad)
    4854:	62 62 62 62 62       	(bad)
    4859:	62 62 62 62 62       	(bad)
    485e:	62 62 62 62 62       	(bad)
    4863:	62 62 62 62 62       	(bad)
    4868:	62 62 62 62 62       	(bad)
    486d:	62 62 62 62 62       	(bad)
    4872:	62 62 62 62 62       	(bad)
    4877:	62 62 62 62 62       	(bad)
    487c:	62 62 62 62 62       	(bad)
    4881:	62 62 62 62 62       	(bad)
    4886:	62 62 62 62 62       	(bad)
    488b:	62 62 62 62 62       	(bad)
    4890:	62 62 62 62 62       	(bad)
    4895:	62 62 62 62 62       	(bad)
    489a:	62 62 62 62 62       	(bad)
    489f:	62 62 62 62 62       	(bad)
    48a4:	62 62 62 62 62       	(bad)
    48a9:	62 62 62 62 62       	(bad)
    48ae:	62 62 62 62 62       	(bad)
    48b3:	62 62 62 62 62       	(bad)
    48b8:	62 62 62 62 62       	(bad)
    48bd:	62                   	(bad)
    48be:	00 00                	add    %al,(%rax)
    48c0:	21 00                	and    %eax,(%rax)
    48c2:	00 00                	add    %al,(%rax)
    48c4:	00 00                	add    %al,(%rax)
	...
