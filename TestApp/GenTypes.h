//  Copyright 2019 The xi-editor authors.

// The contents of this file are autogenerated.

// scene from new (merged) generator

inline uint extract_8bit_value(uint bit_shift, uint package) {
    return (package >> bit_shift) & 255;;
}

inline uint extract_16bit_value(uint bit_shift, uint package) {
    return (package >> bit_shift) & 65535;;
}

#define SIMPLE_GROUP_SIZE 12
#define PIET_ITEM_SIZE 32
#define PietItem_Circle 0
#define PietItem_Line 1
#define PietItem_Fill 2
#define PietItem_Poly 3

typedef uint SimpleGroupRef;
typedef uint PietCircleRef;
typedef uint PietStrokeLineRef;
typedef uint PietFillRef;
typedef uint PietStrokePolyLineRef;
typedef uint PietItemRef;

struct SimpleGroupPacked {
    uint n_items;
    PietItemRef items;
    uint bboxes;
};

inline SimpleGroupPacked SimpleGroup_read(const device char *buf, SimpleGroupRef ref) {
    SimpleGroupPacked result;

    result.n_items = *(device const uint*)(buf + ref);
    result.items = *(device const uint*)(buf + ref + 4);
    result.bboxes = *(device const uint*)(buf + ref + 8);

    return result;
}

inline uint SimpleGroup_n_items(const device char *buf, SimpleGroupRef ref) {
    uint n_items = *(device const uint*)(buf + ref);
    return n_items;
}

inline PietItemRef SimpleGroup_items(const device char *buf, SimpleGroupRef ref) {
    PietItemRef items = *(device const uint*)(buf + ref + 4);
    return items;
}

inline uint SimpleGroup_bboxes(const device char *buf, SimpleGroupRef ref) {
    uint bboxes = *(device const uint*)(buf + ref + 8);
    return bboxes;
}

struct SimpleGroup {
    uint n_items;
    PietItemRef items;
    uint bboxes;
};

inline SimpleGroup SimpleGroup_unpack(SimpleGroupPacked packed_form) {
    SimpleGroup result;

    result.n_items = packed_form.n_items;
    result.items = packed_form.items;
    result.bboxes = packed_form.bboxes;

    return result;
}

struct PietCirclePacked {
    uint tag;
};

inline PietCirclePacked PietCircle_read(const device char *buf, PietCircleRef ref) {
    PietCirclePacked result;

    result.tag = PietItem_Circle;

    return result;
}

struct PietCircle {
};

inline PietCircle PietCircle_unpack(PietCirclePacked packed_form) {
    PietCircle result;

    return result;
}

struct PietStrokeLinePacked {
    uint tag;
    uint flags;
    uint rgba_color;
    float width;
    float2 start;
    float2 end;
};

inline PietStrokeLinePacked PietStrokeLine_read(const device char *buf, PietStrokeLineRef ref) {
    PietStrokeLinePacked result;

    result.tag = PietItem_Line;
    result.flags = *(device const uint*)(buf + ref + 4);
    result.rgba_color = *(device const uint*)(buf + ref + 8);
    result.width = as_type<float>(*(device const uint*)(buf + ref + 12));
    result.start = as_type<float2>(*(device const packed_uint2*)(buf + ref + 16));
    result.end = as_type<float2>(*(device const packed_uint2*)(buf + ref + 24));

    return result;
}

struct PietStrokeLine {
    uint flags;
    uint rgba_color;
    float width;
    float2 start;
    float2 end;
};

inline PietStrokeLine PietStrokeLine_unpack(PietStrokeLinePacked packed_form) {
    PietStrokeLine result;

    result.flags = packed_form.flags;
    result.rgba_color = packed_form.rgba_color;
    result.width = packed_form.width;
    result.start = packed_form.start;
    result.end = packed_form.end;

    return result;
}

struct PietFillPacked {
    uint tag;
    uint flags;
    uint rgba_color;
    uint n_points;
    uint points_ix;
};

inline PietFillPacked PietFill_read(const device char *buf, PietFillRef ref) {
    PietFillPacked result;

    result.tag = PietItem_Fill;
    result.flags = *(device const uint*)(buf + ref + 4);
    result.rgba_color = *(device const uint*)(buf + ref + 8);
    result.n_points = *(device const uint*)(buf + ref + 12);
    result.points_ix = *(device const uint*)(buf + ref + 16);

    return result;
}

struct PietFill {
    uint flags;
    uint rgba_color;
    uint n_points;
    uint points_ix;
};

inline PietFill PietFill_unpack(PietFillPacked packed_form) {
    PietFill result;

    result.flags = packed_form.flags;
    result.rgba_color = packed_form.rgba_color;
    result.n_points = packed_form.n_points;
    result.points_ix = packed_form.points_ix;

    return result;
}

struct PietStrokePolyLinePacked {
    uint tag;
    uint rgba_color;
    float width;
    uint n_points;
    uint points_ix;
};

inline PietStrokePolyLinePacked PietStrokePolyLine_read(const device char *buf, PietStrokePolyLineRef ref) {
    PietStrokePolyLinePacked result;

    result.tag = PietItem_Poly;
    result.rgba_color = *(device const uint*)(buf + ref + 4);
    result.width = as_type<float>(*(device const uint*)(buf + ref + 8));
    result.n_points = *(device const uint*)(buf + ref + 12);
    result.points_ix = *(device const uint*)(buf + ref + 16);

    return result;
}

struct PietStrokePolyLine {
    uint rgba_color;
    float width;
    uint n_points;
    uint points_ix;
};

inline PietStrokePolyLine PietStrokePolyLine_unpack(PietStrokePolyLinePacked packed_form) {
    PietStrokePolyLine result;

    result.rgba_color = packed_form.rgba_color;
    result.width = packed_form.width;
    result.n_points = packed_form.n_points;
    result.points_ix = packed_form.points_ix;

    return result;
}

struct PietItem {
    uint tag;
    uint body[7];
};
inline uint PietItem_tag(const device char *buf, PietItemRef ref) {
    return *(device const uint*)(buf + ref);;
}

// (haven't converted ptcl yet)

typedef uint CmdCircleRef;
typedef uint CmdLineRef;
typedef uint CmdStrokeRef;
typedef uint CmdFillRef;
typedef uint CmdFillEdgeRef;
typedef uint CmdDrawFillRef;
typedef uint CmdSolidRef;
typedef uint CmdRef;

struct CmdCirclePacked {
    uint tag;
    ushort4 bbox;
};

struct CmdLinePacked {
    uint tag;
    float2 start;
    float2 end;
};

struct CmdStrokePacked {
    uint tag;
    float halfWidth;
    uint rgba_color;
};

struct CmdFillPacked {
    uint tag;
    float2 start;
    float2 end;
};

struct CmdFillEdgePacked {
    uint tag;
    int sign;
    float y;
};

struct CmdDrawFillPacked {
    uint tag;
    int backdrop;
    uint rgba_color;
};

struct CmdSolidPacked {
    uint tag;
    uint rgba_color;
};

struct Cmd {
    uint tag;
    uint body[4];
};

Cmd Cmd_read(const device char *buf, CmdRef ref) {
    return *((const device Cmd *)(buf + ref));
}
uint Cmd_tag(const device char *buf, CmdRef ref) {
    return ((const device Cmd *)(buf + ref))->tag;
}
#define Cmd_End 0
#define Cmd_Circle 1
#define Cmd_Line 2
#define Cmd_Fill 3
#define Cmd_Stroke 4
#define Cmd_FillEdge 5
#define Cmd_DrawFill 6
#define Cmd_Solid 7
#define Cmd_Bail 8

CmdCirclePacked CmdCircle_load(const thread Cmd &s) {
    CmdCirclePacked r;
    r.tag = s.tag;
    r.bbox = *((const thread ushort4 *)((const thread char *)&s + 4));
    return r;
}
CmdLinePacked CmdLine_load(const thread Cmd &s) {
    CmdLinePacked r;
    r.tag = s.tag;
    r.start = *((const thread float2 *)((const thread char *)&s + 4));
    r.end = *((const thread float2 *)((const thread char *)&s + 12));
    return r;
}

CmdFillPacked CmdFill_load(const thread Cmd &s) {
    CmdFillPacked r;
    r.tag = s.tag;
    r.start = *((const thread float2 *)((const thread char *)&s + 4));
    r.end = *((const thread float2 *)((const thread char *)&s + 12));
    return r;
}
CmdStrokePacked CmdStroke_load(const thread Cmd &s) {
    CmdStrokePacked r;
    r.tag = s.tag;
    r.halfWidth = *((const thread float *)((const thread char *)&s + 4));
    r.rgba_color = *((const thread uint *)((const thread char *)&s + 8));
    return r;
}

CmdFillEdgePacked CmdFillEdge_load(const thread Cmd &s) {
    CmdFillEdgePacked r;
    r.tag = s.tag;
    r.sign = *((const thread int *)((const thread char *)&s + 4));
    r.y = *((const thread float *)((const thread char *)&s + 8));
    return r;
}

CmdDrawFillPacked CmdDrawFill_load(const thread Cmd &s) {
    CmdDrawFillPacked r;
    r.tag = s.tag;
    r.backdrop = *((const thread int *)((const thread char *)&s + 4));
    r.rgba_color = *((const thread uint *)((const thread char *)&s + 8));
    return r;
}

CmdSolidPacked CmdSolid_load(const thread Cmd &s) {
    CmdSolidPacked r;
    r.tag = s.tag;
    r.rgba_color = *((const thread uint *)((const thread char *)&s + 4));
    return r;
}

inline void CmdCircle_write(device char *buf, CmdCircleRef ref, CmdCirclePacked s) {
    *(device uint*)(buf + ref) = s.tag;
    *(device ushort4*)(buf + ref + 4) = s.bbox;
}

inline void CmdLine_write(device char *buf, CmdLineRef ref, CmdLinePacked s) {
    *(device uint*)(buf + ref) = s.tag;
    *(device packed_uint2*)(buf + ref + 4) = as_type<uint2>(s.start);
    *(device packed_uint2*)(buf + ref + 12) = as_type<uint2>(s.end);
}

inline void CmdStroke_write(device char *buf, CmdStrokeRef ref, CmdStrokePacked s) {
    *(device uint*)(buf + ref) = s.tag;
    *(device uint*)(buf + ref + 4) = as_type<uint>(s.halfWidth);
    *(device uint*)(buf + ref + 8) = s.rgba_color;
}

inline void CmdFill_write(device char *buf, CmdFillRef ref, CmdFillPacked s) {
    *(device uint*)(buf + ref) = s.tag;
    *(device packed_uint2*)(buf + ref + 4) = as_type<uint2>(s.start);
    *(device packed_uint2*)(buf + ref + 12) = as_type<uint2>(s.end);
}

inline void CmdFillEdge_write(device char *buf, CmdFillEdgeRef ref, CmdFillEdgePacked s) {
    *(device uint*)(buf + ref) = s.tag;
    *(device uint*)(buf + ref + 4) = as_type<uint>(s.sign);
    *(device uint*)(buf + ref + 8) = as_type<uint>(s.y);
}

inline void CmdDrawFill_write(device char *buf, CmdDrawFillRef ref, CmdDrawFillPacked s) {
    *(device uint*)(buf + ref) = s.tag;
    *(device uint*)(buf + ref + 4) = as_type<uint>(s.backdrop);
    *(device uint*)(buf + ref + 8) = s.rgba_color;
}

inline void CmdSolid_write(device char *buf, CmdSolidRef ref, CmdSolidPacked s) {
    *(device uint*)(buf + ref) = s.tag;
    *(device uint*)(buf + ref + 4) = s.rgba_color;
}

void Cmd_write_tag(device char *buf, CmdRef ref, uint tag) {
    *(device uint*)(buf + ref) = tag;
}

