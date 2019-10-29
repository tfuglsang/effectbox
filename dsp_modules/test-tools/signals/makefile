.PHONY: signals
signals: FemTalk.f32 cleanguitar_sample.f32\


cleanguitar_sample.f32:
	sox cleanguitar_sample.wav -r 16000 cleanguitar_sample.f32

FemTalk.f32:
	sox FemTalk.wav -r 16000 FemTalk.f32

clean:
	rm -f *.f32
	rm -f *.s16
	
