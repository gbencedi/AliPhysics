#ifndef ALIESDTOOLS_H
#define ALIESDTOOLS_H

class AliPIDResponse;
class TTreeSRedirector;

class AliESDtools : public TNamed
{
  public:
  AliESDtools();
  void Init(TTree* tree);
  void SetStreamer(TTreeSRedirector *streamer){fStreamer=streamer;}
  static Double_t LoadESD(Int_t entry, Int_t verbose);
  /// caching
  Int_t  CacheTPCEventInformation();
  Int_t CalculateEventVariables();
  void TPCVertexFit(TH1F *hisVertex);
  Int_t  GetNearestTrack(const AliExternalTrackParam * trackMatch, Int_t indexSkip, AliESDEvent*event, Int_t trackType, Int_t paramType, AliExternalTrackParam & paramNearest);
  void   ProcessITSTPCmatchOut(AliESDEvent *const esdEvent, AliESDfriend *const esdFriend, TTreeStream *pcstream);
  //
  Int_t DumpEventVariables();
  static Int_t SDumpEventVariables(){return fgInstance->DumpEventVariables();}
  // static functions for querying cached variables in TTree formula
  static Int_t    SCalculateEventVariables(Int_t entry){LoadESD(entry,0); return fgInstance->CalculateEventVariables();}
  static Double_t GetTrackCounters(Int_t index, Int_t toolIndex){return (*fgInstance->fCacheTrackCounters)[index];}
  static Double_t GetTrackTPCCountersZ(Int_t index, Int_t toolIndex){return (*fgInstance->fCacheTrackTPCCountersZ)[index];}
  static Double_t GetTrackdEdxRatio(Int_t index, Int_t toolIndex){return (*fgInstance->fCacheTrackdEdxRatio)[index];}
  static Double_t GetTrackNcl(Int_t index, Int_t toolIndex){return (*fgInstance->fCacheTrackNcl)[index];}
  static Double_t GetTrackChi2(Int_t index, Int_t toolIndex){return (*fgInstance->fCacheTrackChi2)[index];}
  static Double_t GetTrackMatchEff(Int_t index, Int_t toolIndex){return (*fgInstance->fCacheTrackMatchEff)[index];}
  static Double_t GetMeanHisTPCVertexA(){return fgInstance->fHisTPCVertexA->GetMean();}
  static Double_t GetMeanHisTPCVertexC(){return fgInstance->fHisTPCVertexC->GetMean();}
  //
  Int_t fVerbose;                                 // verbosity flag
  TTree *fESDtree;                                //! esd Tree pointer - class is not owner
  AliESDEvent * fEvent;                           //! esd event pointer - class is not owner
  AliPIDResponse   * fPIDResponse;                //! PID response object
  TH1F *fHisTPCVertexA;                           // TPC z vertex A side
  TH1F *fHisTPCVertexC;                           // TPC z vertex C side
  TH1F *fHisTPCVertex;                            //
  TH1F *fHisTPCVertexACut;                        //
  TH1F *fHisTPCVertexCCut;                        //
  TH1F             * fHistPhiTPCCounterA;         // helper histogram phi counters
  TH1F             * fHistPhiTPCCounterC;         // helper histogram phi counters
  TH1F             * fHistPhiTPCCounterAITS;      // helper histogram phi counters
  TH1F             * fHistPhiTPCCounterCITS;      // helper histogram phi counters
  TH1F             * fHistPhiITSCounterA;         // helper histogram phi counters
  TH1F             * fHistPhiITSCounterC;         // helper histogram phi counters
  TVectorF         * fCacheTrackCounters;         // track counter
  TVectorF         * fCacheTrackTPCCountersZ;     // track counter with DCA z cut
  TVectorF         * fCacheTrackdEdxRatio;        // dEdx info counter
  TVectorF         * fCacheTrackNcl;              // ncl counter
  TVectorF         * fCacheTrackChi2;             // chi2 counter
  TVectorF         * fCacheTrackMatchEff;         // matchEff counter
  TGraph           * fLumiGraph;                  // graph for the interaction rate info for a run
  //
  TTreeSRedirector * fStreamer;                  /// streamer
  static AliESDtools* fgInstance;                /// instance of the tool -needed in order to use static functions (for TTreeFormula)
  private:
  AliESDtools(AliESDtools&);
  AliESDtools &operator=(const AliESDtools&);
  ClassDef(AliESDtools, 1) 
};

#endif
